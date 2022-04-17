// Copyright 2022 by Michał Gibas
#include "DataStructure.hpp"

#include "CsvWriter.hpp"
#include "Clock.hpp"

namespace sdizo {

class Benchmark {

public:
    Benchmark(DataStructure* structure, const char* outputFileBaseName);
    virtual ~Benchmark();

    void setSampleSizes(size_t* sampleSizes, size_t count);
    void setRepetitions(size_t repetitions);

    inline void setRemovalIndex(size_t index) { removeIndex = index; }
    inline void setInsertionIndex(size_t index) { insertIndex = index; }

    void run();

private:
    void generateSample();

    void runInsertionBenchmark();
    void runRemovalBenchmark();
    void runSearchBenchmark();

    int* sample = nullptr;

    DataStructure* structure;

    CsvWriter insertWriter, removeWriter, searchWriter;
    Clock clock;

    double* insertionTime, *removalTime, *searchTime;

    size_t* sampleSizes;
    size_t count, repetitions, sampleIndex;
    size_t insertIndex = -1, removeIndex = -1;
};

};