#include "Parser.h"

vector<Token> tokenize(string& str) {
    vector<Token> tokens;
    string buffer;

    for (char c : str) {
        if (isspace(c)) {
            if (!buffer.empty()) {
                if (isdigit(buffer[0]) || buffer[0] == '.') {
                    tokens.push_back({ "NUMBER", buffer, stod(buffer) });
                }
                else if (buffer == "sin" || buffer == "cos" || buffer == "sqrt") {
                    tokens.push_back({ "FUNCTION", buffer });
                }
                else {
                    tokens.push_back({ "VARIABLE", buffer });
                }
                buffer.clear();
            }
            continue;
        }

        if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/') {
            if (!buffer.empty()) {
                if (isdigit(buffer[0]) || buffer[0] == '.') {
                    tokens.push_back({ "NUMBER", buffer, stod(buffer) });
                }
                else if (buffer == "sin" || buffer == "cos" || buffer == "sqrt") {
                    tokens.push_back({ "FUNCTION", buffer });
                }
                else {
                    tokens.push_back({ "VARIABLE", buffer });
                }
                buffer.clear();
            }

            if (c == '(') tokens.push_back({ "LPAREN", "(" });
            else if (c == ')') tokens.push_back({ "RPAREN", ")" });
            else tokens.push_back({ "OPERATOR", string(1, c) });

            continue;
        }

        buffer += c;
    }

    if (!buffer.empty()) {
        if (isdigit(buffer[0]) || buffer[0] == '.') {
            tokens.push_back({ "NUMBER", buffer, stod(buffer) });
        }
        else if (buffer == "sin" || buffer == "cos" || buffer == "sqrt") {
            tokens.push_back({ "FUNCTION", buffer });
        }
        else {
            tokens.push_back({ "VARIABLE", buffer });
        }
    }

    return tokens;
}

double parse(vector<Token>& tokens, int& index, map<string, double>& variables) {
    vector<double> values;
    char op = '+';

    map<string, double> CONSTANTS = {
        {"pi", acos(-1)},
        {"e", 2.71828182845904523536}
    };

    while (index < tokens.size()) {
        Token token = tokens[index++];

        if (token.type == "NUMBER") {
            if (op == '+') values.push_back(token.numValue);
            else if (op == '-') values.push_back(-token.numValue);
            else if (op == '*') values.back() *= token.numValue;
            else if (op == '/') values.back() /= token.numValue;
        }
        else if (token.type == "VARIABLE") {
            auto const_it = CONSTANTS.find(token.value);
            if (const_it != CONSTANTS.end()) {
                double value = const_it->second;
                if (op == '+') values.push_back(value);
                else if (op == '-') values.push_back(-value);
                else if (op == '*') values.back() *= value;
                else if (op == '/') values.back() /= value;
            }
            else {
                if (variables.find(token.value) == variables.end()) {
                    cout << "Enter value for '" << token.value << "': ";
                    cin >> variables[token.value];
                }

                double value = variables[token.value];
                if (op == '+') values.push_back(value);
                else if (op == '-') values.push_back(-value);
                else if (op == '*') values.back() *= value;
                else if (op == '/') values.back() /= value;
            }
        }
        else if (token.type == "FUNCTION") {
            if (index >= tokens.size() || tokens[index].type != "LPAREN") {
                throw runtime_error("Expected '(' after function");
            }
            index++;

            double arg = parse(tokens, index, variables);

            index++;

            double result;
            if (token.value == "sin") result = sin(arg);
            else if (token.value == "cos") result = cos(arg);
            else if (token.value == "sqrt") result = sqrt(arg);
            else throw runtime_error("Unknown function: " + token.value);

            if (op == '+') values.push_back(result);
            else if (op == '-') values.push_back(-result);
            else if (op == '*') values.back() *= result;
            else if (op == '/') values.back() /= result;
        }
        else if (token.type == "LPAREN") {
            double value = parse(tokens, index, variables);

            if (op == '+') values.push_back(value);
            else if (op == '-') values.push_back(-value);
            else if (op == '*') values.back() *= value;
            else if (op == '/') values.back() /= value;
        }
        else if (token.type == "RPAREN") {
            break;
        }
        else if (token.type == "OPERATOR") {
            op = token.value[0];
        }
    }

    double result = 0;
    for (double val : values) {
        result += val;
    }
    return result;
}