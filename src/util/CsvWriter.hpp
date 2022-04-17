#ifndef CSV_WRITER_HPP
#define CSV_WRITER_HPP

#include <fstream>

namespace sdizo {

class CsvWriter {

public:
    CsvWriter(const char* fileName) : outputStream(fileName) {}
    virtual ~CsvWriter() { outputStream.close(); }

    template<typename T> void write(T data) {
        outputStream << data << ", ";
    }

    void newLine() {
        outputStream << '\n';
    }

private:
    std::ofstream outputStream;

};

};

#endif // CSV_WRITER_HPP