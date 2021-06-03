#include "BinReader.h"

BinReader::BinReader(const std::string& path) : k(0), f(0.0), x('0') {
    file.open(path, std::ios::binary);
}

char BinReader::readByte() {
    file.read((char*)&x, 1);
    return x;
}

bool BinReader::readBit() {
    if (k == 8) {
        readByte();
        k = 0;
    }
    bool b = (x >> k) & 1;
    k++;
    return b;
}

int BinReader::readInt() {
    file.read((char*)&k, 4);
    return k;
}

float BinReader::readFloat() {
    file.read((char*)&f, 4);
    return f;
}

