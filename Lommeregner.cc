#include <iostream>
#include <vector>
#include <string>

enum class Token {
    Plus,
    Minus,
    Prod,
    Div,
    Num,
    OpenParen,
    CloseParen
};

 void lexString(std::string rawText, std::vector<std::pair<Token,std::string> >& tokenOut) {
    for(size_t i = 0; i < rawText.size(); i++) {
        switch(rawText[i])
        {
        case '+':
            tokenOut.push_back(std::make_pair(Token::Plus,std::string("+")));
            break;
        case '-':
            tokenOut.push_back(std::make_pair(Token::Minus,std::string("-")));
            break;
        case '*':
            tokenOut.push_back(std::make_pair(Token::Prod,std::string("*")));
            break;
        case '/':
            tokenOut.push_back(std::make_pair(Token::Div,std::string("/")));
            break;
        case '(':
            tokenOut.push_back(std::make_pair(Token::OpenParen,std::string("(")));
            break;
        case ')':
            tokenOut.push_back(std::make_pair(Token::CloseParen,std::string(")")));
            break;
        case ' ':
            //ignore spaces
            break;
        default:
            if('0' <= rawText[i] && rawText[i] <= '9') {
                size_t j = 0;
                //Empty loop body, j is length of num; Shortcircuit means we never access the right side of && if it would overflow
                for(; i+j < rawText.size() && ('0' <= rawText[i+j] && rawText[i+j] <= '9'); j++) {}
                tokenOut.push_back(std::make_pair(Token::Num,rawText.substr(i,j)));
                //after parsing number increase i
                i = i+j;
            } else {
                //does not recognize the symbol.
            }
            break;
        }
    }
 }

int main(int argc, char* argv[]) {
    std::string input = "";
    std::vector<std::pair<Token, std::string> > tokens{};

    std::cout<<"Lommeregner:\n"<<"Skriv et udtryk der bruger +,-,*,/\n";
    while(1) {
        std::cout<<">";
        std::getline(std::cin, input);
        lexString(input, tokens);
    }
    
}