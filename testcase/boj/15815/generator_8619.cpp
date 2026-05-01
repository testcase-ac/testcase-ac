#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    int sizeType = rnd.next(0, 2);   // 0: small, 1: medium, 2: larger
    int shapeType = rnd.next(0, 2);  // 0: operands-early, 1: balanced, 2: ops-early
    int digitMode = rnd.next(0, 2);  // 0: 0-9, 1: 0-3, 2: 7-9
    bool preferDiv = rnd.next(0, 1) == 1;

    int minOps, maxOps;
    if (sizeType == 0) {
        minOps = 0; maxOps = 3;   // length 1..7
    } else if (sizeType == 1) {
        minOps = 4; maxOps = 8;   // length 9..17
    } else {
        minOps = 9; maxOps = 14;  // length 19..29
    }

    int ops = rnd.next(minOps, maxOps);
    int numsTotal = ops + 1;
    int numsLeft = numsTotal;
    int opsLeft = ops;

    double opBias;
    if (shapeType == 0) opBias = 0.2;   // fewer early ops
    else if (shapeType == 1) opBias = 0.5;
    else opBias = 0.8;                  // more early ops

    string expr;
    vector<long long> st;

    auto getDigit = [&]() -> int {
        if (digitMode == 0) {
            return rnd.next(0, 9);
        } else if (digitMode == 1) {
            return rnd.next(0, 3);
        } else {
            return rnd.next(7, 9);
        }
    };

    while (numsLeft + opsLeft > 0) {
        bool canOp = (opsLeft > 0 && st.size() >= 2);
        bool canNum = (numsLeft > 0);
        bool chooseOp = false;

        if (!canOp) {
            chooseOp = false;
        } else if (!canNum) {
            chooseOp = true;
        } else {
            chooseOp = (rnd.next() < opBias);
        }

        if (!chooseOp) {
            // Place an operand
            int d = getDigit();
            st.push_back(d);
            expr.push_back(char('0' + d));
            numsLeft--;
        } else {
            // Place an operator
            long long b = st.back(); st.pop_back();
            long long a = st.back(); st.pop_back();

            vector<char> opsList = {'+', '-', '*', '/'};
            shuffle(opsList.begin(), opsList.end());
            if (preferDiv) {
                // Move '/' to the front if present
                for (int i = 0; i < (int)opsList.size(); ++i) {
                    if (opsList[i] == '/') {
                        swap(opsList[0], opsList[i]);
                        break;
                    }
                }
            }

            bool found = false;
            long long v = 0;
            char chosen = '+';

            for (char c : opsList) {
                if (c == '+') {
                    v = a + b;
                } else if (c == '-') {
                    v = a - b;
                } else if (c == '*') {
                    v = a * b;
                } else if (c == '/') {
                    if (b == 0) continue;
                    v = a / b; // truncation toward zero, same as int
                }

                long long av = v >= 0 ? v : -v;
                if (av <= 2147483647LL) {
                    chosen = c;
                    found = true;
                    break;
                }
            }

            // There should always be a safe operator; just in case, fall back to subtraction
            if (!found) {
                v = a - b;
                chosen = '-';
            }

            st.push_back(v);
            expr.push_back(chosen);
            opsLeft--;
        }
    }

    // At this point, we should have exactly one value on the stack
    // and expr is a valid postfix expression.
    println(expr);

    return 0;
}
