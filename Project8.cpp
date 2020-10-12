#include <string>
#include "Project8.h"
#include "Parse.h"

bool failure = false;
string failedvar;

vector<string> getVector(SymbTable &symb){
    vector<string> vec;
    while (next_token_type == SYMBOL || next_token_type == NUMBER || next_token_type == NAME){
        string token = next_token();
        if (token == "//"){
            skip_line();
            break;
        }
        if (next_token_type == NAME){
            if (token == "text" || token == "output" || token == "set" || token == "var"){
                break;
            }
            if (symb.find(token)){
                int value = symb.getValue(token);
                vec.push_back(to_string(value));
            }
            else {
                failure = true;
                failedvar = token;
                read_next_token();
                while (next_token_type == SYMBOL || next_token_type == NUMBER || next_token_type == NAME){
                    string check = next_token();
                    if (check == "text" || check == "output" || check == "set" || check == "var"){
                        break;
                    }
                    read_next_token();
                }
                break;
            }
        }
        else {
            vec.push_back(token);
        }
        read_next_token();
        token = next_token();
    }
    return vec;
}

void processText(SymbTable &symb){
    read_next_token();
    string token = next_token();
    cout << token;
}

void processOutput(SymbTable &symb){
    read_next_token();
    if (next_token_type == NUMBER){
        int value = token_number_value;
        cout << value;
        read_next_token();
    }
    else if (next_token_type == SYMBOL){
        vector<string> vec = getVector(symb);
        if (failure){
            cout << "ERROR: Variable " << failedvar << " does not exist!";
            failure = false;
        }
        else {
            ExpTree* exptree = new ExpTree(vec);
            cout << exptree->eval();
        }
    }
    else if (next_token_type == NAME){
        string variable = next_token();
        if (symb.find(variable)){
            cout << symb.getValue(variable);
        }
        else {
            cout << "ERROR: Variable " << variable << " does not exist!";
        }
        read_next_token();
    }
}

void processSet(SymbTable &symb){
    read_next_token();
    string variable = next_token();
    if (symb.find(variable)){ //variable existed
        read_next_token();
        if (next_token_type == NUMBER){
            int value = token_number_value;
            symb.setValue(variable, value);
            read_next_token();
        }
        else {
            vector<string> vec = getVector(symb);
            if (failure){
                cout << "ERROR: Variable " << failedvar << " does not exist!" << endl;
                failure = false;
            }
            else {
                ExpTree *exp = new ExpTree(vec);
                int value = exp->eval();
                symb.setValue(variable, value);
            }
        }
    }
    else { //variable did not exist
        read_next_token();
        if (next_token_type == NUMBER){
            int value = token_number_value;
            symb.insert(variable, value);
            read_next_token();
            cout << "WARNING: Variable " << variable << " does not exist! Value was created." << endl;
        }
        else {
            vector<string> vec = getVector(symb);
            if (failure){
                cout << "ERROR: Variable " << failedvar << " does not exist!";
                failure = false;
            }
            else {
                ExpTree *exp = new ExpTree(vec);
                int value = exp->eval();
                symb.insert(variable, value);
                cout << "WARNING: Variable " << variable << " does not exist! Value was created." << endl;
            }

        }
    }


}

void processVar(SymbTable &symb){
    read_next_token();
    string variable = next_token();
    if(symb.find(variable)){ //variable existed
        read_next_token();
        if (next_token_type == NUMBER){
            int value = token_number_value;
            symb.setValue(variable, value);
            read_next_token();
            cout << "WARNING: Variable " << variable << " already exists! Value was updated." << endl;
        }
        else {
            vector<string> vec = getVector(symb);
            if (failure){
                cout << "ERROR: Variable " << failedvar << " does not exist!";
                failure = false;
            }
            else {
                ExpTree *exp = new ExpTree(vec);
                int value = exp->eval();
                symb.setValue(variable, value);
                cout << "WARNING: Variable " << variable << " already exists! Value was updated." << endl;
            }
        }
    }
    else { //variable did not exist
        read_next_token();
        if (next_token_type == NUMBER){
            int value = token_number_value;
            symb.insert(variable, value);
            read_next_token();
        }
        else {
            vector<string> vec = getVector(symb);
            if (failure){
                cout << "ERROR: Variable " << failedvar << " does not exist!";
                failure = false;
            }
            else {
                ExpTree *exp = new ExpTree(vec);
                int value = exp->eval();
                symb.insert(variable, value);
            }
        }
    }
}



