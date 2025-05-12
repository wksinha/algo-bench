#ifndef HASHING_H
#define HASHING_H

#include <bitset>
#include <random>

class Hashing {
public:
    Hashing();
    std::bitset<32> getBits() const;
    void regenerate();

private:
    std::bitset<32> bits;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};

#endif