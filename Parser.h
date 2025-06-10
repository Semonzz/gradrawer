#pragma once
#include "Head.h"

struct Token {
    string type;
    string value;
    double numValue = 0.0;
};

vector<Token> tokenize(string& str);
double parse(vector<Token>& tokens, int& index, map<string, double>& variables);