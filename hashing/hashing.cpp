#include "hashing.h"

Hashing::Hashing()
    : gen(rd()), dist(0, 1)
{
    regenerate();
}

std::bitset<32> Hashing::getBits() const {
    return bits;
}

void Hashing::regenerate() {
    for (int i = 0; i < 32; ++i) {
        bits[i] = dist(gen);
    }
}
