// Copyright 2022 by Michał Gibas
#include "DataStructure.hpp"

#include "CsvWriter.hpp"
#include "Clock.hpp"

namespace sdizo {

/* Utility class for measuring structure's performance */
class Benchmark {

public:
    Benchmark(DataStructure* structure, const char* outputFileBaseName);
    virtual ~Benchmark();

    void setSampleSizes(size_t* sampleSizes, size_t count);
    void setRepetitions(size_t repetitions);
    
    inline void setRemovalIndex(size_t index) { removeIndex = index; }
    inline void setInsertionIndex(size_t index) { insertIndex = index; }
    inline void setRandomSample(bool randomSample) { this->randomSample = randomSample; }

    void run();

private:
    void generateSample();

    void insertSampleIntoStructure();
    void clearStructure();

    void runInsertionBenchmark();
    void runRemovalBenchmark();
    void runSearchBenchmark();

    int* sample = nullptr;

    DataStructure* structure;

    bool randomSample = true;

    CsvWriter writer;
    Clock clock;

    double insertionTime, removalTime, searchTime;

    size_t* sampleSizes;
    size_t count, repetitions, sampleIndex;
    size_t insertIndex = -1, removeIndex = -1;
};

};