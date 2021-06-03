#ifndef VAJA4_BINWRITER_H
#define VAJA4_BINWRITER_H

#include <iostream>
#include <fstream>

class BinWriter {
public:
    std::ofstream file;
    char x;
    int k;

    BinWriter(const std::string &path);
    ~BinWriter();

    void writeByte(const char &x);
    void writeBit(const bool &b);
    void writeInt(const int &y);
    void writeFloat(const float &f);
};


#endif //VAJA4_BINWRITER_H
