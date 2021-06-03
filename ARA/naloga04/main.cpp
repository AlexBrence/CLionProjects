#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include "BinReader.h"
#include "BinWriter.h"

void nastaviSlovar1(std::unordered_map<std::string, unsigned int>& slovar, const int maxVelikostSlovarja) {
    if (!slovar.empty()) slovar.clear();
    slovar.reserve(maxVelikostSlovarja);

    for (int i = 0; i < 256; i++) {
        std::string tmp;
        tmp += (char)i;
        slovar[tmp] = i;
    }
}


bool compress(std::unordered_map<std::string, unsigned int>& slovar, const std::string& filePath, const int maxVelikostSlovarja) {
    BinReader br(filePath);
    BinWriter bw("/home/alex/CLionProjects/ARA/naloga04/out.bin");
    unsigned int indexSlovar = 256;
    long long charCounter = 0, bitCounter = 0;
    long charCounterResets = 1, bitCounterResets = 1;   // 1 because I can multiply it later with xCounter
    const unsigned int steviloBitov = ceil(log2(maxVelikostSlovarja + 1));
    std::stack<bool> bin;

    if (!br.file.is_open()) {
        std::cout << "File " << filePath << " not found!\n";
        return false;
    }
    if (!bw.file.is_open()) {
        std::cout << "Couldn't write to file!\n";
        return false;
    }

    std::string T;
    while (!br.file.eof()) {
       char C = br.readByte();
        T += C;

        // Preprecim morebitni overflow
        if (charCounter == LLONG_MAX) {
            charCounter = 0;
            charCounterResets++;
        }
        charCounter++;

        // Ce je ze v slovarju nadaljujem z naslednjo crko
        std::unordered_map<std::string, unsigned int>::const_iterator it = slovar.find(T);
        if (it != slovar.end()) {
            continue;
        }

        // Sicer grem po korakih
        if (indexSlovar == maxVelikostSlovarja) {
            nastaviSlovar1(slovar, maxVelikostSlovarja);
            indexSlovar = 256;
        }

        // Dodaj v slovar
        slovar[T] = indexSlovar;
        indexSlovar++;

        // Zapisi index od T v binarnem zapisu
        std::vector<bool>tmp(steviloBitov);
        for (int i = 0; i < steviloBitov; i++) {
            bin.push(((slovar[T] >> i) & 1));
        }
        while (!bin.empty()) {
            bw.writeBit(bin.top());
            bin.pop();
        }
        if (bitCounter == LLONG_MAX) {
            bitCounter = 0;
            bitCounterResets++;
        }
        bitCounter++;
        T = "";
        T += C;
    }
    bw.file.close();

    // Izracun kompresije
    std::cout << "Kompresijsko razmerje: "
              << (float)(charCounterResets * charCounter * 8) / (bitCounterResets * bitCounter * steviloBitov)
              << std::endl;
    return true;
}


int main(int argc, const char* argv[]) {
    if (argc != 4) return -1;
    std::unordered_map<std::string, unsigned int> slovar;
    if (argv[1][0] == 'c') {
        nastaviSlovar1(slovar, std::stoi(argv[2]));

        if (!compress(slovar, argv[3], std::stoi(argv[2]))) {
            std::cout << "Error while compressing!";
        }
    }

    return 0;
}