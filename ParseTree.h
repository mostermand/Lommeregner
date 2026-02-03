#include <memory>
#include "Lexing.h"

class ParseTree {
public:
    ParseTree();
    ParseTree(TokenVector toks);
    void parse(TokenVector toks);
private:
    std::unique_ptr<ParseTree> left;
    std::unique_ptr<ParseTree> right;
};