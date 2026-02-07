#ifndef PARSETREE_H
#define PARSETREE_H

#include <memory>
#include "Lexing.h"

class ParseTree {
public:
    ParseTree(); //leaves ParseTree uninitialized
    ParseTree(const TokenVector& toks); //Initializes by parsing the TokenVector
    ParseTree(int num); //Initializes to leaf node with value num
    ParseTree(TokenId label, std::unique_ptr<ParseTree> left, std::unique_ptr<ParseTree> right);
    void parse(const TokenVector& toks);
    TokenId getLabel() const;
    ParseTree& getLeft() const;
    ParseTree& getRight() const;
    int getNum() const;
private:
    //Label of root this subtree
    TokenId label;
    //The left and right ...
    std::unique_ptr<ParseTree> left;
    std::unique_ptr<ParseTree> right;
    //Numerical value if leaf is true
    int num;
};

#endif