#include "../../include/parser/Lexer.hpp"
#include <cctype>
#include <sstream>

TokenType Lexer::classify(const std::string& token) {
    if (token.empty()) return TokenType::Unknown;
    
    if (isFlag(token)) return TokenType::Flag;
    if (isNumber(token)) return TokenType::Number;
    if (isFloat(token)) return TokenType::Float;
    
    return TokenType::Word;
}

bool Lexer::isNumber(const std::string& token) {
    if (token.empty()) return false;
    size_t start = 0;
    if (token[0] == '-' || token[0] == '+') start = 1;
    
    if (start == token.length()) return false;
    
    for (size_t i = start; i < token.length(); ++i) {
        if (!std::isdigit(token[i])) return false;
    }
    return true;
}

bool Lexer::isFloat(const std::string& token) {
    if (token.empty()) return false;
    size_t start = 0;
    if (token[0] == '-' || token[0] == '+') start = 1;
    
    bool hasDot = false;
    for (size_t i = start; i < token.length(); ++i) {
        if (token[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (!std::isdigit(token[i])) {
            return false;
        }
    }
    return hasDot;
}

bool Lexer::isFlag(const std::string& token) {
    return token.length() > 1 && token[0] == '-';
}