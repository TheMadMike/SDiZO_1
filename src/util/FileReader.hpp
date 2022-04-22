// Copyright 2022 by Michał Gibas
#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <fstream>

namespace sdizo {

class FileReader {

public:
    FileReader(const char* fileName) : inputStream(fileName){
        if(!inputStream.is_open()) {
            throw new std::runtime_error("Could not open a file! Try again");
        }
    }
    virtual ~FileReader() { inputStream.close(); }

    template<typename T> T readNext(){
        if(inputStream.eof())
            throw new std::runtime_error("EOF");

        T buffer;
        inputStream >> buffer;

        return buffer;
    }

private:
    std::ifstream inputStream;
};

};

#endif //FILE_READER_HPP