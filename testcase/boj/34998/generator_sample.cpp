#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

string digit(int value) {
    return string(1, char('0' + value));
}

vector<string> makeSafeExpression(int x) {
    vector<string> operands;
    int remaining = rnd.next(x + 1, 9);
    for (int i = 0; i <= x; ++i) {
        int slotsLeft = x - i;
        int low = 1;
        int high = remaining - slotsLeft;
        int value = (i == x) ? remaining : rnd.next(low, high);
        operands.push_back(digit(value));
        remaining -= value;
    }
    shuffle(operands.begin(), operands.end());
    return operands;
}

vector<string> makeOverflowExpression(int x) {
    vector<string> operands = makeSafeExpression(x);
    int pos = rnd.next(0, x);
    int value = operands[pos][0] - '0';
    operands[pos] = digit(rnd.next(value, 9));
    int sum = 0;
    for (const string& operand : operands) {
        sum += operand[0] - '0';
    }
    if (sum < 10) {
        operands[rnd.next(0, x)] = "9";
    }
    return operands;
}

vector<string> makeBangExpression(int x) {
    vector<string> operands;
    int bangCount = rnd.next(1, x + 1);
    for (int i = 0; i < bangCount; ++i) {
        operands.push_back("!");
    }
    while ((int)operands.size() <= x) {
        operands.push_back(digit(rnd.next(1, 9)));
    }
    shuffle(operands.begin(), operands.end());
    return operands;
}

void printCase(int x, const vector<string>& operands) {
    println(x);
    for (int i = 0; i <= x; ++i) {
        if (i > 0) {
            printf(" + ");
        }
        printf("%s", operands[i].c_str());
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = (mode == 4) ? 50 : rnd.next(8, 24);
    println(n);

    for (int tc = 0; tc < n; ++tc) {
        int x = rnd.next(1, 3);
        int type = (tc < 3) ? tc : rnd.next(0, 2);

        vector<string> operands;
        if (mode == 0 || type == 0) {
            operands = makeSafeExpression(x);
        } else if (mode == 1 || type == 1) {
            operands = makeOverflowExpression(x);
        } else {
            operands = makeBangExpression(x);
        }

        printCase(x, operands);
    }

    return 0;
}
