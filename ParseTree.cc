#include "ParseTree.h"

ParseTree::ParseTree() : label(TokenId::InvalidId) {}

ParseTree::ParseTree(const TokenVector& toks) : label(TokenId::InvalidId) {
    this->parse(toks);
}

ParseTree::ParseTree(int num) : label(TokenId::Num) {
    this->num = num;
}

ParseTree::ParseTree(TokenId label, std::unique_ptr<ParseTree> left, std::unique_ptr<ParseTree> right) : label(label), left(std::move(left)), right(std::move(right)) {}

void ParseTree::parse(const TokenVector& toks) {
    int stage = 0; //which 
    int parenDepth = 0;
    std::vector<int> stageStack;
    std::vector<TokenId> labelStack;
    std::vector<std::unique_ptr<ParseTree> > leftStack, rightStack;

    for(auto tokenIterator = toks.begin(); tokenIterator != toks.end(); ++tokenIterator) {
        switch(tokenIterator->first)
        {
        //Fallthrough
        case TokenId::Plus:
        case TokenId::Minus:
        case TokenId::Prod:
        case TokenId::Div:
            switch(this->label)
            {
            case TokenId::Plus:
            case TokenId::Minus:
            case TokenId::Prod:
            case TokenId::Div:
                if(this->right) {
                    this->left.reset(new ParseTree(this->label, std::move(this->left), std::move(this->right)));
                } else {
                    //error: left argument is partially applied
                }
                break;
            case TokenId::Num:
                this->left.reset(new ParseTree(this->num));
                break;
            case TokenId::InvalidId:
            default:
                break;
            }
            this->label = tokenIterator->first;
            break;
        case TokenId::Num:
            switch(this->label)
            {
            case TokenId::Plus:
            case TokenId::Minus:
            case TokenId::Prod:
            case TokenId::Div:
                if(!this->right) {
                    this->right.reset(new ParseTree(std::stoi(tokenIterator->second)));
                } else {
                    //aplying full expression to num
                }
                break;
            case TokenId::Num:
                //error applying num to num
                break;
            case TokenId::InvalidId:
                this->label = TokenId::Num;
                this->num = std::stoi(tokenIterator->second);
                break;
            default:
                break;
            }
            break;
        case TokenId::OpenParen:
            ++parenDepth;
            stageStack.push_back(stage);
            leftStack.push_back(std::move(this->left));
            rightStack.push_back(std::move(this->right));
            labelStack.push_back(this->label);
            stage = 0;
            break;
        case TokenId::CloseParen:
            if(parenDepth != 0) {
                --parenDepth;
                this->left.reset(new ParseTree(this->label, std::move(this->left), std::move(this->right)));

                stage = stageStack.back();
                stageStack.pop_back();

                this->label = labelStack.back();
                labelStack.pop_back();
            } else {
                //error closed paren without matching open paren
            }
            break;
        case TokenId::InvalidId:
        default:
            break;
        }
        ++stage;
    }
}

void ParseTree::clear() {
    this->label = TokenId::InvalidId;
    this->left.reset(nullptr);
    this->right.reset(nullptr);
    this->num = 0;
}

TokenId ParseTree::getLabel() const {
    return this->label;
}

ParseTree& ParseTree::getLeft() const {
    return *this->left;
}

ParseTree& ParseTree::getRight() const {
    return *this->right;
}

int ParseTree::getNum() const {
    return this->num;
}