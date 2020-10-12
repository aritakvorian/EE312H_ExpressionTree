#include <string>
#include <vector>
#include "ExpressionTree.hpp"

using namespace std;

class SymbTable {

    class Node {
    public:
        string name;
        int val;
        Node *left;
        Node *right;

        Node(string name) {
            name = name;
            this->val = 0;
            this->left = nullptr;
            this->right = nullptr;
        }

        Node(string name, int value){
            this->name = name;
            this->val = value;
            this->left = nullptr;
            this->right = nullptr;
        }

        Node(const Node &other);
        ~Node();

    };

    Node *root;

    void copy(const SymbTable &other);
    void destroy();

 public:

    SymbTable();
    SymbTable(const SymbTable &other);
    SymbTable& operator=(const SymbTable &other);
    ~SymbTable();

    void insert(string name);
    void insert(string name, int value);
    bool find(string name) const;
    int getValue(string name);
    void setValue (string name, int value);
};
