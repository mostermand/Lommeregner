#include "Lexing.h"

void lexString(std::string rawText, TokenVector& tokenOut) {
    for(size_t i = 0; i < rawText.size(); i++) {
        switch(rawText[i])
        {
        case '+':
            tokenOut.push_back(std::make_pair(TokenId::Plus,std::string("+")));
            break;
        case '-':
            tokenOut.push_back(std::make_pair(TokenId::Minus,std::string("-")));
            break;
        case '*':
            tokenOut.push_back(std::make_pair(TokenId::Prod,std::string("*")));
            break;
        case '/':
            tokenOut.push_back(std::make_pair(TokenId::Div,std::string("/")));
            break;
        case '(':
            tokenOut.push_back(std::make_pair(TokenId::OpenParen,std::string("(")));
            break;
        case ')':
            tokenOut.push_back(std::make_pair(TokenId::CloseParen,std::string(")")));
            break;
        case ' ':
            //ignore spaces
            break;
        default:
            if('0' <= rawText[i] && rawText[i] <= '9') {
                size_t j = 0;
                //Empty loop body, j is length of num; Shortcircuit means we never access the right side of && if it would overflow
                for(; i+j < rawText.size() && ('0' <= rawText[i+j] && rawText[i+j] <= '9'); j++) {}
                tokenOut.push_back(std::make_pair(TokenId::Num,rawText.substr(i,j)));
                //after parsing number increase i to index of last digit of number
                i = i+j - 1;
            } else {
                //does not recognize the symbol.
            }
            break;
        }
    }
}