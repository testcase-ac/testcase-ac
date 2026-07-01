#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string variable() {
    return string(1, char('a' + rnd.next(0, 25)));
}

string expression(int depth);

string factor(int depth) {
    if (depth <= 0 || rnd.next(0, 2) == 0) {
        return variable();
    }

    string inner = expression(depth - 1);
    int layers = rnd.next(1, 3);
    while (layers--) {
        inner = "(" + inner + ")";
    }
    return inner;
}

string product(int depth) {
    int terms = rnd.next(1, depth <= 0 ? 2 : 4);
    string result;
    for (int i = 0; i < terms; ++i) {
        result += factor(depth - 1);
    }
    return result;
}

string expression(int depth) {
    int terms = rnd.next(1, depth <= 0 ? 1 : 4);
    string result = product(depth);
    for (int i = 1; i < terms; ++i) {
        result += "+" + product(depth - 1);
    }
    return result;
}

string wrappedSumInProduct() {
    string left = product(2);
    string middle = "(" + expression(2) + ")";
    string right = product(1);
    if (rnd.next(0, 1) == 0) {
        return left + middle;
    }
    return middle + right;
}

string redundantParentheses() {
    string result = expression(2);
    int layers = rnd.next(2, 5);
    while (layers--) {
        result = "(" + result + ")";
    }
    return result;
}

string longAssociativeChain() {
    int terms = rnd.next(8, 18);
    string result = variable();
    for (int i = 1; i < terms; ++i) {
        if (rnd.next(0, 1) == 0) {
            result += "+" + variable();
        } else {
            result += variable();
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int case_count = rnd.next(4, 12);
    vector<string> cases;
    cases.push_back(variable());
    cases.push_back(wrappedSumInProduct());
    cases.push_back(redundantParentheses());
    cases.push_back(longAssociativeChain());

    while ((int)cases.size() < case_count) {
        int mode = rnd.next(0, 4);
        string expr;
        if (mode == 0) {
            expr = expression(rnd.next(1, 3));
        } else if (mode == 1) {
            expr = wrappedSumInProduct();
        } else if (mode == 2) {
            expr = redundantParentheses();
        } else if (mode == 3) {
            expr = longAssociativeChain();
        } else {
            expr = "(" + product(2) + ")+(" + expression(2) + ")";
        }

        if ((int)expr.size() <= 1000) {
            cases.push_back(expr);
        }
    }

    for (const string& expr : cases) {
        println(expr);
    }
    return 0;
}
