// Copyright 2022 by Michał Gibas

#include "Benchmark.hpp"
#include <random>
#include <functional>

namespace sdizo {

Benchmark::Benchmark(DataStructure* structure, const char* fileBaseName)
:structure(structure),
insertWriter(std::string(fileBaseName).append("_insert.csv").c_str()),
removeWriter(std::string(fileBaseName).append("_remove.csv").c_str()),
searchWriter(std::string(fileBaseName).append("_search.csv").c_str()) {

}

Benchmark::~Benchmark() {
    delete[] sample;
}

typedef std::default_random_engine RandomEngine;
typedef std::uniform_int_distribution<int> IntDistribution;

void logData(size_t index, double averageTime, size_t sampleSize, CsvWriter& writer) {
    writer.write<unsigned long>(index);
    writer.write(averageTime);
    writer.write<unsigned long>(sampleSize);
    writer.newLine();
}

void Benchmark::run() {
    insertWriter.write("position/index, average time [us], sample size"); insertWriter.newLine();
    searchWriter.write("position/index, average time [us], sample size"); searchWriter.newLine();
    removeWriter.write("position/index, average time [us], sample size"); removeWriter.newLine();

    for(size_t i = 0; i < count; ++i) {
        sampleIndex = i;
        size_t sampleSize = sampleSizes[sampleIndex];

        insertionTime = new double[sampleSize];
        removalTime = new double[sampleSize];
        searchTime = new double[sampleSize];

        for(size_t j = 0; j < repetitions; ++j) {
            generateSample();

            runInsertionBenchmark(); // insert data
            runSearchBenchmark(); // search through it
            runRemovalBenchmark(); // remove it
        }

        for(size_t j = 0; j < sampleSize; ++j) {
            logData(j, insertionTime[j] / static_cast<double>(repetitions), sampleSize, insertWriter);
            logData(j, searchTime[j] / static_cast<double>(repetitions), sampleSize, searchWriter);
            logData(j, removalTime[j] / static_cast<double>(repetitions), sampleSize, removeWriter);
        }


        delete[] insertionTime;
        delete[] removalTime;
        delete[] searchTime;
    }

}

void Benchmark::runInsertionBenchmark() {
    size_t sampleSize = sampleSizes[sampleIndex];

    for(size_t i = 0; i < sampleSize; ++i) {

        if(insertIndex == -3) {
            clock.start();
            structure->add(sample[i], (i / 2UL) - 1);
            clock.stop();

            insertionTime[i] += clock.getDurationUs();
            continue;
        }

        clock.start();
        structure->add(sample[i], insertIndex);
        clock.stop();

        insertionTime[i] += clock.getDurationUs();

    }

}

void Benchmark::runRemovalBenchmark() {
    size_t sampleSize = sampleSizes[sampleIndex];
    for(size_t i = 0; i < sampleSize; ++i) {
        
        if(insertIndex == -3) {
            clock.start();
            structure->remove((i*2UL) % sampleSize);
            clock.stop();
            
            insertionTime[i] += clock.getDurationUs();
            continue;
        }

        clock.start();
        structure->remove(removeIndex);
        clock.stop();
               
        removalTime[i] += clock.getDurationUs();
    }

}

void Benchmark::runSearchBenchmark() {
    size_t sampleSize = sampleSizes[sampleIndex];
    for(size_t i = 0; i < sampleSize; ++i) {
        
        clock.start();
        size_t index = structure->find(sample[i]);
        clock.stop();

        searchTime[i] += clock.getDurationUs();
    }
}

void Benchmark::setSampleSizes(size_t* sampleSizes, size_t count) {
    this->sampleSizes = sampleSizes;
    this->count = count;
}

void Benchmark::setRepetitions(size_t repetitions) {
    this->repetitions = repetitions;
}

void Benchmark::generateSample() {
    size_t sampleSize = sampleSizes[sampleIndex];

    delete[] sample;
    sample = new int[sampleSize];

    RandomEngine engine;
    IntDistribution distribution(0, sampleSize);
    auto generate = std::bind(distribution, engine);

    for(size_t i = 0; i < sampleSize; ++i) {
        sample[i] = generate();
    }
}

};