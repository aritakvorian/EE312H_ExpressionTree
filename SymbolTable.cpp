#include <iostream>
#include "SymbolTable.hpp"
#include <string>


using namespace std;

SymbTable::SymbTable() : root(nullptr) {
}

void SymbTable::destroy() {
    delete root;
}

SymbTable::~SymbTable(){
    destroy();
}

SymbTable::Node::~Node() {
    delete left;
    delete right;
}

SymbTable::Node::Node(const Node &other) {
    name = other.name;
    val = other.val;
    left = (other.left == nullptr) ? nullptr : new Node(*(other.left));
    right = (other.right == nullptr) ? nullptr : new Node(*(other.right));
}

void SymbTable::copy(const SymbTable &other) {
    root = new Node(*(other.root));    
}

SymbTable::SymbTable(const SymbTable &other) {
    copy(other);
}

SymbTable& SymbTable::operator=(const SymbTable &other) {
    if (this == &other) {
        return *this;
    }
    destroy();
    root = new Node(*(other.root));
    return *this;
}

bool SymbTable::find(string name) const {
    Node *current = root;

    while (current != nullptr) {
        if (current->name == name) {
            return true;
        }
        if (name < current->name) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

void SymbTable::insert(string name) {
    Node *n = new Node(name);

    if (root == nullptr) {
        root = n;
    } else {
        Node *prev = nullptr;
        Node *current = root;
        while (current != nullptr) {
            prev = current;
            if (name < current->name) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (name < prev->name) {
            prev->left = n;
        } else {
            prev->right = n;
        }
    }
}

void SymbTable::insert(string name, int value) {
    Node *n = new Node(name, value);

    if (root == nullptr) {
        root = n;
    } else {
        Node *prev = nullptr;
        Node *current = root;
        while (current != nullptr) {
            prev = current;
            if (name < current->name) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (name < prev->name) {
            prev->left = n;
        } else {
            prev->right = n;
        }
    }
}

int SymbTable::getValue(string name) {
    if(this->find(name)){
        Node *current = root;
        while (current != nullptr) {
            if (current->name == name) {
                return current->val;
            }
            if (name < current->name) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
    else {
        cout << "ERROR: Variable '" << name << "' does not exist!";
    }
    return 0;
}

void SymbTable::setValue(string name, int value) {
    if (this->find(name)){
        Node *current = root;

        while (current != nullptr) {
            if (current->name == name) {
                current->val = value;
            }
            if (name < current->name) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
    else {
        insert(name, value);
    }
}
