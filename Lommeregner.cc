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

 std::vector<Token> lexString(std::string rawText);

int main(int argc, char* argv[]) {
    std::string input = "";
    std::cout<<"Lommeregner:\n"<<"Skriv et udtryk der bruger +,-,*,/\n";
    while(1)
    {
        std::cout<<">";
        std::getline(std::cin, input);
        std::cout<<input;
    }
    
}