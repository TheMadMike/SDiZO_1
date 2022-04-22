// Copyright 2022 by Michał Gibas

#include "Benchmark.hpp"
#include <random>
#include <functional>

namespace sdizo {

Benchmark::Benchmark(DataStructure* structure, const char* fileBaseName)
:structure(structure), writer(fileBaseName) {

}

Benchmark::~Benchmark() {
    delete[] sample;
}

void logData(const char* operationName, double averageTime, size_t sampleSize, CsvWriter& writer) {
    writer.write(operationName);
    writer.write(averageTime);
    writer.write<unsigned long>(sampleSize);
    writer.newLine();
}

void Benchmark::run() {
    writer.write("operation, average time [us], sample size"); writer.newLine();

    for(size_t i = 0; i < count; ++i) {
        sampleIndex = i;
        size_t sampleSize = sampleSizes[sampleIndex];

        insertionTime = 0.0;
        removalTime = 0.0;
        searchTime = 0.0;

        for(size_t j = 0; j < repetitions; ++j) {
            generateSample();
            insertSampleIntoStructure();

            runInsertionBenchmark(); // perform single insertion
            runSearchBenchmark(); // perform single search
            runRemovalBenchmark(); // perform single removal

            clearStructure();
        }

        logData("Insertion", insertionTime / static_cast<double>(repetitions), sampleSize, writer);
        logData("Search", searchTime / static_cast<double>(repetitions), sampleSize, writer);
        logData("Removal", removalTime / static_cast<double>(repetitions), sampleSize, writer);

    }

}

void Benchmark::clearStructure() {
    size_t sampleSize = sampleSizes[sampleIndex];
    for(size_t i = 0; i < sampleSize; ++i) {
        structure->remove();
    }

}

void Benchmark::runSearchBenchmark() {
    size_t sampleSize = sampleSizes[sampleIndex];
        
    clock.start();
    size_t index = structure->find(sample[sampleSize - 1]);
    clock.stop();

    searchTime += clock.getDurationUs();
}

void Benchmark::insertSampleIntoStructure() {

    size_t sampleSize = sampleSizes[sampleIndex];
    for(size_t i = 0; i < sampleSize; ++i) {
        structure->add(sample[i]);
    }
}

void Benchmark::runInsertionBenchmark() {
    size_t sampleSize = sampleSizes[sampleIndex];

    if(insertIndex == -3) {
        clock.start();
        structure->add(1, sampleSize / 2);
        clock.stop();

        insertionTime += clock.getDurationUs();
    
    } else {

        clock.start();
        structure->add(1, insertIndex);
        clock.stop();
        insertionTime += clock.getDurationUs();
    }

    structure->removeByValue(structure->find(1));
    
}

void Benchmark::runRemovalBenchmark() {
    size_t sampleSize = sampleSizes[sampleIndex];
        
    if(removeIndex == -3) {
        clock.start();
        structure->remove(((sampleSize-1)/2) % sampleSize);
        clock.stop();
        
        removalTime += clock.getDurationUs();
        return;
    }
    if(removeIndex == -4) {
        clock.start();
        structure->removeByValue(structure->find(sample[sampleSize - 1]));
        clock.stop();
        removalTime += clock.getDurationUs();
        return;
    }

    clock.start();
    structure->remove(removeIndex);
    clock.stop();
    
            
    removalTime += clock.getDurationUs();
}

void Benchmark::setSampleSizes(size_t* sampleSizes, size_t count) {
    this->sampleSizes = sampleSizes;
    this->count = count;
}

void Benchmark::setRepetitions(size_t repetitions) {
    this->repetitions = repetitions;
}

typedef std::default_random_engine RandomEngine;
typedef std::uniform_int_distribution<int> IntDistribution;

void Benchmark::generateSample() {
    size_t sampleSize = sampleSizes[sampleIndex];

    delete[] sample;
    sample = new int[sampleSize];

    if(randomSample) {

        RandomEngine engine;
        IntDistribution distribution(0, sampleSize*2UL);
        auto generate = std::bind(distribution, engine);

        for(size_t i = 0; i < sampleSize; ++i) {
            sample[i] = generate();
        }

        return;
    }

    long int value = sampleSize-1;
    for(size_t i = 0; i < sampleSize; ++i) {
        sample[i] = value;
        --value;
    }
}

};