#include "../../include/parser/Tokenizer.hpp"
#include <sstream>

std::vector<std::string> Tokenizer::tokenize(std::istream& input) {
    std::string line;
    if (!std::getline(input, line)) {
        return {};
    }
    return tokenizeString(line);
}

std::vector<std::string> Tokenizer::tokenizeString(const std::string& str) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}
