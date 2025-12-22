#pragma once
#include <string>
#include <vector>

enum class TokenType {
    Number,
    Float,
    Word,
    Flag,
    Unknown
};

class Lexer {
public:
    static TokenType classify(const std::string& token);
    static bool isNumber(const std::string& token);
    static bool isFloat(const std::string& token);
    static bool isFlag(const std::string& token);
};