#ifndef LEXING_H
#define LEXING_H

#include <utility>
#include <string>
#include <vector>

enum class TokenId {
    Plus,
    Minus,
    Prod,
    Div,
    Num,
    OpenParen,
    CloseParen
};

typedef std::pair<TokenId,std::string> Token;
typedef std::vector<Token> TokenVector;

void lexString(std::string rawText, TokenVector& tokenOut);

#endif