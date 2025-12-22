#pragma once
#include <istream>
#include <vector>
#include <string>

class Tokenizer {
public:
    static std::vector<std::string> tokenize(std::istream& input);
    static std::vector<std::string> tokenizeString(const std::string& str);
};