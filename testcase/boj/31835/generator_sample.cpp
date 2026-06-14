#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomValue() {
    return rnd.next(0, 1) == 0 ? 'F' : 'T';
}

char randomOperator() {
    return rnd.next(0, 1) == 0 ? '&' : '|';
}

int oddSize(int minTerms, int maxTerms) {
    int terms = rnd.next(minTerms, maxTerms);
    return 2 * terms - 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<string> tokens;

    if (mode == 0) {
        n = 1;
        tokens.push_back(string(1, randomValue()));
    } else {
        if (mode == 6) {
            n = rnd.next(0, 1) == 0 ? 1999 : oddSize(100, 250);
        } else {
            n = oddSize(2, mode == 1 ? 4 : 20);
        }

        tokens.reserve(n);
        char fixedOp = randomOperator();
        char fixedValue = randomValue();
        for (int i = 1; i <= n; ++i) {
            if (i % 2 == 1) {
                char value;
                if (mode == 2) {
                    value = fixedValue;
                } else if (mode == 3) {
                    value = ((i / 2) % 2 == 0) ? 'T' : 'F';
                } else if (mode == 4) {
                    value = rnd.next(0, 99) < 80 ? fixedValue : randomValue();
                } else {
                    value = randomValue();
                }
                tokens.push_back(string(1, value));
            } else {
                char op;
                if (mode == 2) {
                    op = fixedOp;
                } else if (mode == 3) {
                    op = ((i / 2) % 2 == 0) ? '&' : '|';
                } else if (mode == 5) {
                    op = rnd.next(0, 99) < 85 ? fixedOp : randomOperator();
                } else {
                    op = randomOperator();
                }
                tokens.push_back(string(1, op));
            }
        }
    }

    println(n);
    println(tokens);
    println(string(1, randomValue()));

    return 0;
}
