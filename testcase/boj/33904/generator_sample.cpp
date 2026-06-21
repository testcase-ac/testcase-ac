#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string forLine(int depth, char variable) {
    return string(depth, ' ') + "for (int " + variable + " = 1; " + variable + " < 9; " + variable + "++)";
}

bool isVariable(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

string trimExpression(string expression) {
    if ((int)expression.size() > 20) {
        expression.resize(20);
    }
    while (!expression.empty() && expression.back() == ' ') {
        expression.pop_back();
    }
    if (expression.empty()) {
        return "0";
    }
    return expression;
}

string spacedExpression(const vector<char>& variables, int maxTerms) {
    vector<char> terms = variables;
    shuffle(terms.begin(), terms.end());

    int count = rnd.next(1, min((int)terms.size(), maxTerms));
    string expr;
    for (int i = 0; i < count; ++i) {
        if (!expr.empty()) {
            expr += rnd.any(vector<string>{"+", "-", "*", "/", "%", " + ", " - "});
        }
        expr += terms[i];
        if (rnd.next(3) == 0 && (int)expr.size() <= 17) {
            expr += rnd.any(vector<string>{"+1", "-2", "*3"});
        }
    }
    return trimExpression(expr);
}

string randomExpression(const vector<char>& declared) {
    vector<char> letters = declared;
    string allLetters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (char c : allLetters) {
        if (find(letters.begin(), letters.end(), c) == letters.end() && rnd.next(4) == 0) {
            letters.push_back(c);
        }
    }
    if (letters.empty()) {
        letters.push_back(rnd.any(allLetters));
    }

    int mode = rnd.next(5);
    if (mode == 0) {
        return to_string(rnd.next(0, 999));
    }
    if (mode == 1) {
        return spacedExpression(letters, 4);
    }

    string alphabet = "0123456789+-*/%()[]{}<>=!?:;.,_ ";
    string expr;
    int target = rnd.next(1, 20);
    bool previousVariable = false;
    while ((int)expr.size() < target) {
        bool chooseVariable = rnd.next(100) < 35 && !previousVariable;
        char c = chooseVariable ? rnd.any(letters) : rnd.any(alphabet);
        if (expr.empty() && c == ' ') {
            continue;
        }
        expr += c;
        previousVariable = isVariable(c);
    }
    return trimExpression(expr);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string variablePool = "ijkabcXYZnN";
    int depth = rnd.next(1, 12);
    int mode = rnd.next(4);

    vector<char> variables;
    for (int i = 0; i < depth; ++i) {
        char variable;
        if (mode == 0 && i > 0 && rnd.next(100) < 45) {
            variable = rnd.any(variables);
        } else if (mode == 1) {
            variable = variablePool[i % (int)variablePool.size()];
        } else {
            variable = rnd.any(variablePool);
        }
        variables.push_back(variable);
    }

    for (int i = 0; i < depth; ++i) {
        println(forLine(i, variables[i]));
    }
    println(string(depth, ' ') + randomExpression(variables));

    return 0;
}
