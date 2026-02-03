#include <iostream>
#include <vector>
#include <string>

enum class Token {
    Plus,
    Minus,
    Div,
    Num,
    OpenParen,
    CloseParen
};

 int lexString(std::string rawText) {
    for(size_t i = 0; i < rawText.size(); i++) {
        switch(rawText[i])
        {
        case '+':
        case '-':
        case '/':
        case '(':
        case ')':
        default:
            if('0' <= rawText[i] && rawText[i] <= '9') {

            }
            break;
        }
    }
 }

int main(int argc, char* argv[]) {
    std::string input = "";
    std::cout<<"Lommeregner:\n"<<"Skriv et udtryk der bruger +,-,*,/\n";
    while(1) {
        std::cout<<">";
        std::getline(std::cin, input);
        std::cout<<input;
    }
    
}