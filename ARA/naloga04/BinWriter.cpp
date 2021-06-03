#include "BinWriter.h"

BinWriter::BinWriter(const std::string &path) : k(0), x('0') {
    file.open(path, std::ios::binary);
}

BinWriter::~BinWriter() {
    if (k > 0) writeByte(x);
    file.close();
}

void BinWriter::writeByte(const char &x) {
    file.write((char*)&x, 1);
}

void BinWriter::writeBit(const bool &b) {
    if (k == 8) {
        writeByte(x);
        k = 0;
    }
    x ^= (-b ^ x) & (1 << k);
    k++;
}

void BinWriter::writeInt(const int &y) {
    file.write((char*)&k, 4);
}

void BinWriter::writeFloat(const float &f) {
    file.write((char*)&f, 4);
}