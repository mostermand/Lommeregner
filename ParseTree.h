#ifndef PARSETREE_H
#define PARSETREE_H

#include <memory>
#include "Lexing.h"

class ParseTree {
public:
    ParseTree(); //leaves ParseTree uninitialized
    ParseTree(TokenVector toks); //Initializes by parsing the TokenVector
    ParseTree(int num); //Initializes to leaf node with value num
    ParseTree(TokenId label, std::unique_ptr<ParseTree> left, std::unique_ptr<ParseTree> right);
    void parse(TokenVector toks);
    bool isLeaf();
private:
    //Label of root this subtree
    TokenId label;
    //The left and right ...
    std::unique_ptr<ParseTree> left;
    std::unique_ptr<ParseTree> right;
    //If true left and right point to nothing
    bool leaf;
    //Numerical value if leaf is true
    int num;
};

#endif