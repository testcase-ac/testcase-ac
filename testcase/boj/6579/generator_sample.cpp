#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeSetLiteral(int alphabetSize) {
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alphabetSize = min(alphabetSize, (int)letters.size());
    letters.resize(alphabetSize);
    shuffle(letters.begin(), letters.end());

    int size = rnd.next(0, alphabetSize);
    string chosen = letters.substr(0, size);
    sort(chosen.begin(), chosen.end());
    return "{" + chosen + "}";
}

char randomOperator(bool allowIntersection) {
    string ops = allowIntersection ? "+-*" : "+-";
    return rnd.any(ops);
}

string makeFactor(int depth, int alphabetSize);

string makeExpression(int depth, int alphabetSize) {
    int terms = rnd.next(1, depth <= 1 ? 2 : 4);
    string expr = makeFactor(depth, alphabetSize);
    for (int i = 1; i < terms; ++i) {
        expr += randomOperator(true);
        expr += makeFactor(depth, alphabetSize);
    }
    return expr;
}

string makeFactor(int depth, int alphabetSize) {
    if (depth <= 0 || rnd.next(100) < 55) {
        return makeSetLiteral(alphabetSize);
    }
    return "(" + makeExpression(depth - 1, alphabetSize) + ")";
}

string makeLongChain(int alphabetSize) {
    string expr = makeSetLiteral(alphabetSize);
    while (true) {
        string next = expr + randomOperator(true) + makeSetLiteral(alphabetSize);
        if ((int)next.size() > 240) {
            return expr;
        }
        expr = next;
    }
}

string makePrecedenceCase(int alphabetSize) {
    string a = makeSetLiteral(alphabetSize);
    string b = makeSetLiteral(alphabetSize);
    string c = makeSetLiteral(alphabetSize);
    string d = makeSetLiteral(alphabetSize);

    if (rnd.next(2) == 0) {
        return a + "+" + b + "*" + c + "-" + d;
    }
    return "(" + a + "+" + b + ")*(" + c + "-" + d + ")";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int lines = rnd.next(5, 12);
    int alphabetSize = rnd.next(3, 26);
    vector<string> expressions;

    expressions.push_back(makeSetLiteral(alphabetSize));
    expressions.push_back(makePrecedenceCase(alphabetSize));
    expressions.push_back(makeLongChain(alphabetSize));

    while ((int)expressions.size() < lines) {
        int depth = rnd.next(1, 4);
        string expr = makeExpression(depth, alphabetSize);
        if (!expr.empty() && (int)expr.size() <= 255) {
            expressions.push_back(expr);
        }
    }

    shuffle(expressions.begin(), expressions.end());
    for (const string& expr : expressions) {
        println(expr);
    }

    return 0;
}
