#ifndef VAJA4_BINREADER_H
#define VAJA4_BINREADER_H

#include <iostream>
#include <fstream>

class BinReader {
public:
    std::ifstream file;
    int k;
    char x;
    float f;

    BinReader(const std::string& path);

    char readByte();
    bool readBit();
    int readInt();
    float readFloat();
};


#endif //VAJA4_BINREADER_H
