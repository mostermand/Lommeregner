#include <iostream>
#include <vector>
#include <string>

#include "Lexing.h"
#include "ParseTree.h"

int evalTokenList(TokenVector tokenList) {
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

int eval(const ParseTree& tree) {
    switch(tree.getLabel())
    {
    case TokenId::Plus:
        return eval(tree.getLeft()) + eval(tree.getRight());
        break;
    case TokenId::Minus:
        return eval(tree.getLeft()) - eval(tree.getRight());
        break;
    case TokenId::Prod:
        return eval(tree.getLeft()) * eval(tree.getRight());
        break;
    case TokenId::Div:
        return eval(tree.getLeft()) / eval(tree.getRight());
        break;
    case TokenId::Num:
        return tree.getNum();
        break;
    default:
        std::cout<<"Error: invalid TokenId of ParseTree\n";
        return -1;
    }
}

int main(int argc, char* argv[]) {
    std::string input = "";
    TokenVector tokens{};
    ParseTree tree;

    std::cout<<"Lommeregner:\n"<<"Skriv et udtryk der bruger +,-,*,/\n";
    while(1) {
        std::cout<<">";
        std::getline(std::cin, input);
        lexString(input, tokens);
        tree.parse(tokens);
        std::cout<<eval(tree)<<std::endl;

        tokens.clear();
    }
    
}