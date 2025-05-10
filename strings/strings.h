#ifndef STRINGS_H
#define STRINGS_H

#include <string>
#include <vector>

class Strings {
public:
    static std::vector<int> searchPatternKMP(std::string& text, std::string& pattern);
    static std::vector<int> searchPatternRK(std::string& text, std::string& pattern);
    static std::vector<int> searchPatternZ(std::string& text, std::string& pattern);
    static std::vector<int> subpalindromesManacher(std::string& s);
    static std::vector<int> subpalindromesRK(std::string& s);
};

# endif