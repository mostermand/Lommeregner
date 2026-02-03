#include <iostream>
#include <vector>
#include <string>

#include "Lexing.h"
 
 int eval(TokenVector tokenList) {
    int result = 0;
    if(tokenList.size() == 3) {
        switch(tokenList[1].first)
        {
        case TokenId::Plus:
            return std::stoi(tokenList[0].second) + std::stoi(tokenList[2].second);
        case TokenId::Minus:
            return std::stoi(tokenList[0].second) - std::stoi(tokenList[2].second);
        case TokenId::Prod:
            return std::stoi(tokenList[0].second) * std::stoi(tokenList[2].second);
        case TokenId::Div:
            if(std::stoi(tokenList[2].second) == 0) {
                std::cout<<"Division med 0\n";
            } else {
                return std::stoi(tokenList[0].second) / std::stoi(tokenList[2].second);
            }
            
        
        default:
            break;
        }
    }
    std::cout<<"Brug <num1>[+-*/]<num2>";
    return -1;
 }

int main(int argc, char* argv[]) {
    std::string input = "";
    TokenVector tokens{};

    std::cout<<"Lommeregner:\n"<<"Skriv et udtryk der bruger +,-,*,/\n";
    while(1) {
        std::cout<<">";
        std::getline(std::cin, input);
        lexString(input, tokens);
        std::cout<<eval(tokens)<<std::endl;

        tokens.clear();
    }
    
}