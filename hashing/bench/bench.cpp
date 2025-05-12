#include "../hashing.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <functional>

const Hashing hashing;

unsigned int rollingHash(std::string& s) {
    const int p = 31;
    const int m = 1e9 + 9;

    std::vector<long long> p_pow(std::max(s.size(), s.size()));
    p_pow[0] = 1;
    for (int i = 1; i < p_pow.size(); i++) {
        p_pow[i] = (p_pow[i-1] * p) % m;
    }

    long long h = 0;
    for (int i = 0; i < s.size(); i++) {
        h = (h + (s[i] + 1) * p_pow[i]) % m;
    }

    return (unsigned int) h;
}

unsigned int stdHash(std::string& s) {
    return std::hash<std::string>{}(s);
}

unsigned int xorHash(std::string& s) {
    unsigned int hash = 0;
    for (int i = 0; i < s.size(); i += 4) {
        int temp = 0;
        for (int j = i; j < std::min((int) s.size(), i + 4); j++) {
            temp += (s[j] >> ((j - i) * 8));
        }
        hash ^= temp;
    }
    return hash;
}

unsigned int uniformHash(std::string& s) {
    unsigned int hash = 0;
    for (int i = 0; i < s.size(); i += 4) {
        int temp = 0;
        for (int j = i; j < std::min((int) s.size(), i + 4); j++) {
            temp += (s[j] >> ((j - i) * 8));
        }
        hash ^= temp;
    }
    return hash;
}

unsigned int bitDiffCount(unsigned int a, unsigned int b) {
    return __builtin_popcount(a ^ b);
}

unsigned int applyHash(const std::function<unsigned int(std::string&)>& hashFunc, std::string& input1, std::string& input2) {
    unsigned int h1 = hashFunc(input1);
    unsigned int h2 = hashFunc(input2);
    return bitDiffCount(h1, h2);
}

unsigned int applyHash(unsigned int num) {
    unsigned int hash = 0;
    auto bits = hashing.getBits();
    for (int i = 0; i < 32; i++) {
        hash |= (bits[i] * (num & (1L << i)));
    }
    unsigned int m = 999'983;
    return hash % m;
}

std::string generateRandomString(int length) {
    const std::string charset = "abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, charset.size() - 1);

    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += charset[dist(gen)];
    }
    return result;
}

void printStats(const std::string& name, std::vector<int>& deltas) {
    std::string filename = name + ".flips.txt";
    std::ofstream file(filename);
    for (int i = 0; i < 33; i++) {
        file << deltas[i] << " ";
    }
    file.close();
}

const int TESTS = 5'000;
const int STRING_LEN = 256;

int main() {
    std::vector<int> rollingHashDeltas(33, 0);
    std::vector<int> stdHashDeltas(33, 0);
    std::vector<int> xorHashDeltas(33, 0);
    std::vector<int> randomHashDeltas(33, 0);

    for (int t = 0; t < TESTS; t++) {
        std::string a = generateRandomString(256);
        std::string b = a;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, a.size() - 1);
        
        int idx = dist(gen);
        std::uniform_int_distribution<> bitDist(0, 8);
        b[idx] ^= (1 << bitDist(gen));
        
        rollingHashDeltas[applyHash(rollingHash, a, b)]++;
        stdHashDeltas[applyHash(stdHash, a, b)]++;
        xorHashDeltas[applyHash(xorHash, a, b)]++;


        unsigned int randomInt = 0;
        std::uniform_int_distribution<> zeroOneDist(0, 1);
        for (int i = 0; i < 32; i++) {
            randomInt += ((long long) zeroOneDist(gen)) << i;
        }
        std::uniform_int_distribution<> chooseBitDist(0, 31);
        int diff = bitDiffCount(applyHash(randomInt), applyHash((randomInt ^ (1 << chooseBitDist(gen)))));
        randomHashDeltas[diff]++;
    }

    printStats("rolling-hash", rollingHashDeltas);
    printStats("std-hash", stdHashDeltas);
    printStats("xor-hash", xorHashDeltas);
    printStats("random-hash", randomHashDeltas);

    return 0;
}