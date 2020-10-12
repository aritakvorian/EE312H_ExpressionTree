#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

using namespace std;

class ExpTree {

    class Node {
    private:
        bool is_operand;
        int operand;
        string optr;
        Node *left;
        Node *right;

    public:
        Node(const int operand) {
            this->is_operand = true;
            this->operand = operand;
            this->optr = '0';
            this->left = nullptr;
            this->right = nullptr;
        }

        Node(string optr, Node* left, Node *right) {
            this->is_operand = false;
            this->operand = 0;
            this->optr = optr;
            this->left = left;
            this->right = right;
        }

        int32_t eval() const {
            if (is_operand) {
                return operand;
            } else {
                if (optr == "!"){
                    int32_t lv = left->eval();
                    return !lv;
                }
                else if (optr == "~"){
                    int32_t  lv = left->eval();
                    return -1*lv;
                }
                int32_t lv = left->eval();
                int32_t rv = right->eval();
                if (optr == "+") {
                    return lv + rv;
                } else if (optr == "*") {
                    return lv * rv;
                } else if (optr == "-") {
                    return lv - rv;
                } else if (optr == "/") {
                    return lv/rv;
                } else if (optr == "%") {
                    return lv % rv;
                } else if (optr == ">"){
                    return lv > rv;
                } else if (optr == "<"){
                    return lv < rv;
                } else if (optr == "=="){
                    return lv == rv;
                } else if (optr == "!="){
                    return lv != rv;
                } else if (optr == ">="){
                    return lv >= rv;
                } else if (optr == "<="){
                    return lv <= rv;
                } else if (optr == "&&"){
                    return lv && rv;
                } else if (optr == "||") {
                    return lv || rv;
                }
            }
            return 0;
        }


        Node(const Node &other){
            is_operand = other.is_operand;
            operand = other.operand;
            optr = other.optr;
            left = (other.left == nullptr) ? nullptr : new Node(*(other.left));
            right = (other.right == nullptr) ? nullptr : new Node(*(other.right));
        }

        void Destroy(Node *n){
            if (n != NULL)
            {
                Destroy(n->left);
                Destroy(n->right);
                delete n;
            }
        }

        ~Node() {}

        Node& operator=(const Node &other){
            if (this == &other){
                return *this;
            }
            is_operand = other.is_operand;
            operand = other.operand;
            optr = other.optr;
            left = (other.left == nullptr) ? nullptr : new Node(*(other.left));
            right = (other.right == nullptr) ? nullptr : new Node(*(other.right));
            return *this;
        }

        void printInfix() const {
            if (is_operand) {
                cout << operand << ' ';
            } else {
                if (left != nullptr) {
                    left->printInfix();
                }
                cout << optr << ' ';
                if (right != nullptr) {
                    right->printInfix();
                }
            }
        }

        void printPrefix() const {
            if (is_operand) {
                cout << operand << ' ';
            } else {
                cout << optr << ' ';
                if (left != nullptr) {
                    left->printPrefix();
                } 
                if (right != nullptr) {
                    right->printPrefix();
                }
            }
        }

        string valAsString() const {
            int result = this->eval();
            return std::to_string(result);
        }


    };

    /* root of the expression tree */
    Node *root;

    Node* parse(vector<string> &expr){
        if (expr.size() == 0) {
            return nullptr;
        }

        string token = expr[0];
        expr.erase(expr.begin());
        if (token == "+" || token == "-" || token == "*" || token == "%" || token == "/" || token == "<" || token == ">" || token == "<=" || token == "==" || token == ">=" || token == "!=" || token == "&&" || token == "||" || token ==  "!" || token == "~") {
            Node *left = parse(expr);
            Node *right = parse(expr);
            return new Node(token, left, right);
        } else {
            return new Node(stoi(token));
        }
    }

    void printInfix(const Node *n) const {
        n->printInfix();
    }

    void printPrefix(const Node *n) const {
        n->printPrefix();
    }

public:

    ExpTree(vector<string> expr) {
        this->root = parse(expr);
    }

    ExpTree(const ExpTree &other) {
        root = new Node(*(other.root));
    }

    void DestroyTree(Node* n){
        if (n != nullptr)
        {
            n->Destroy(n);
        }
    }

     ~ExpTree() {
        DestroyTree(root);
    }

    ExpTree& operator=(const ExpTree &other){
        if (this == &other){
            return *this;
        }
        delete root;
        root = new Node(*(other.root));
        return *this;
    }

    /* Print the tree by doing in-order traversal */
    void printInfix() const {
        root->printInfix();
    }

    /* Print the tree by doing pre-order traversal */
    void printPrefix() const {
        root->printPrefix();
    }

    /* Evaluate the tree and return the value */
    int32_t eval() const {
        if (root == nullptr) {
            return 0;
        } else {
            return root->eval();
        }
    }
};
