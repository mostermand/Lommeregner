#include "ParseTree.h"

ParseTree::ParseTree() : leaf(false) {}
ParseTree::ParseTree(TokenVector toks) : leaf(false) {
    this->parse(toks);
}

ParseTree::ParseTree(int num) : leaf(true) {
    this->num = num;
}

ParseTree::ParseTree(TokenId label, std::unique_ptr<ParseTree> left, std::unique_ptr<ParseTree> right) : label(label), left(std::move(left)), right(std::move(right)), leaf(false) {}

void ParseTree::parse(TokenVector toks) {
    int stage = 0; //which 
    int parenDepth = 0;
    std::vector<int> stageStack;
    std::vector<TokenId> labelStack;
    std::vector<std::unique_ptr<ParseTree> > leftStack, rightStack;

    for(auto it = toks.begin(); it != toks.end(); ++it) {
        switch(it->first)
        {
            //Fallthrough
        case TokenId::Plus:
        case TokenId::Minus:
        case TokenId::Prod:
        case TokenId::Div:
            if(stage == 1) {
                this->label = it->first;
            } else {
                //error
            }
            break;
        case TokenId::Num:
            switch(stage)
            {
            case 0:
                if(!this->left) {
                    this->left.reset(new ParseTree(std::stoi(it->second)));
                } else {
                    //left is not empty, perhaps error
                }
                break;
            case 1:
                //invalid use of number as operator
                break;
            case 2:
                if(!this->right) {
                    this->right.reset(new ParseTree(std::stoi(it->second)));
                } else {
                    //right is not empty perhaps error
                }
                break;
            default:
                //error
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
                stage = stageStack.back();
                stageStack.pop_back();
                switch(stage)
                {
                case 0:
                    if(!this->left) {
                        this->left.reset(new ParseTree(this->label, std::move(this->left), std::move(this->right)));
                    } else {
                        //left is not empty, perhaps error
                    }
                    break;
                case 1:
                    //error expression used as operator
                    break;
                case 2:
                    if(!this->right) {
                        this->right.reset(new ParseTree(this->label, std::move(this->left), std::move(this->right)));
                    } else {
                        //right is not empty, perhaps error
                    }
                    break;
                }
                this->label = labelStack.back();
                labelStack.pop_back();
            } else {
                //error closed paren without matching open paren
            }
            break;
        }
        ++stage;
        if(stage >= 3) {
            //error more than 3 (2 args, 1 operator) stages
        }
    }
    /*
    std::vector<int> stageStack;
    // -1: when parsing larg, 0: when parsing operator, 1: when parsing rarg
    int stage = -1;
    int parenDepth = 0;
    for(auto it = toks.begin(); it != toks.end(); ++it) {
        switch(it->first)
        {
        case TokenId::Num:
            switch(stage)
            {
            case -1:
                this->left = new ParseTree(std::stoi(it->second));
                ++stage;
                break;
            case 1:
                this->right = new ParseTree(std::stoi(it->second));
                break;
            default:
                //error, probably a number used as operator
            }
            break;
        case TokenId::OpenParen:
            ++parenDepth;
            stageStack.push_back(stage);
            stage = -1;
            break;
        case TokenId::CloseParen:
            if(parenDepth != 0 && stage == 1) {
                --parenDepth;
                stage = stageStack.back();
                stageStack.pop_back();
            } else {
                //error closed parenthesis without matching opening or body of paren pair is not a full expression
            }
            break;
        //fallthrough
        case TokenId::Plus:
        case TokenId::Minus:
        case TokenId::Prod:
        case TokenId::Div:
            this->label = it->first;
            break;
        default:
            //error should never happen
        }
    }
    */
}

bool ParseTree::isLeaf() const {
    return this->leaf;
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