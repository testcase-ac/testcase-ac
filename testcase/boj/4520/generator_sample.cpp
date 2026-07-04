#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

// Generates compact valid dice expressions that exercise constants, dice terms,
// signs, and six-dice boundary cases under the local validator contract.
string makeExpression() {
    const vector<int> sides = {4, 6, 8, 12, 20};
    vector<string> terms;
    int totalDice = 0;

    int mode = rnd.next(0, 5);
    int termCount = rnd.next(1, 5);
    if (mode == 3) {
        termCount = rnd.next(4, 6);
    }

    for (int i = 0; i < termCount; ++i) {
        bool forceConstant = mode == 0 || totalDice == 6;
        bool forceDice = !forceConstant && (mode == 1 || mode == 3);
        bool useDie = forceDice || (!forceConstant && rnd.next(0, 99) < 65);

        if (useDie) {
            int remaining = 6 - totalDice;
            int count = mode == 3 ? 1 : rnd.next(1, remaining);
            if (mode == 4 && i == 0) {
                count = remaining;
            }
            int side = sides[rnd.next(int(sides.size()))];
            terms.push_back(to_string(count) + "d" + to_string(side));
            totalDice += count;
        } else {
            terms.push_back(to_string(rnd.next(1, 10)));
        }
    }

    if (terms.empty()) {
        terms.push_back("1");
    }

    string expression = terms[0];
    for (int i = 1; i < int(terms.size()); ++i) {
        char op = rnd.next(0, 99) < 55 ? '+' : '-';
        expression += op;
        expression += terms[i];
    }
    return expression;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 20);
    println(n);

    for (int i = 0; i < n; ++i) {
        int target;
        int targetMode = rnd.next(0, 4);
        if (targetMode == 0) {
            target = 0;
        } else if (targetMode == 1) {
            target = 100;
        } else {
            target = rnd.next(1, 30);
        }

        println(target, makeExpression());
    }

    return 0;
}
