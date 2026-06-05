#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

namespace {

const long long kIntMin = -(1LL << 31);
const long long kIntMax = (1LL << 31) - 1;

long long apply(long long lhs, long long rhs, char op) {
    if (op == 0) {
        return lhs;
    }
    if (op == 'S') {
        return lhs - rhs;
    }
    if (op == 'M') {
        return lhs * rhs;
    }
    if (op == 'U') {
        return lhs / rhs;
    }
    return lhs + rhs;
}

string numberText(int value, bool allowLeadingZeroes) {
    string s = to_string(value);
    if (allowLeadingZeroes && rnd.next(3) == 0) {
        s = string(rnd.next(1, 3), '0') + s;
    }
    return s;
}

int chooseOperand(char op, long long lhs) {
    if (op == 'U') {
        int value = rnd.next(1, 20);
        if (rnd.next(4) == 0) {
            value = rnd.next(1, 3);
        }
        return value;
    }
    if (op == 'M') {
        if (llabs(lhs) > 1000000 && rnd.next(2) == 0) {
            return rnd.next(0, 1);
        }
        return rnd.next(0, 20);
    }
    return rnd.next(0, 1000);
}

char chooseBinaryOp(long long lhs) {
    vector<char> ops = {'S', 'M', 'U', 'P'};
    shuffle(ops.begin(), ops.end());
    for (char op : ops) {
        int rhs = chooseOperand(op, lhs);
        if (op == 'U' && rhs == 0) {
            continue;
        }
        long long next = apply(lhs, rhs, op);
        if (kIntMin <= next && next <= kIntMax) {
            return op;
        }
    }
    return 'P';
}

void appendBinary(string& expr, int& alphabetCount, long long& lhs, long long& rhs,
                  char& pending,
                  bool& readingRhs, bool allowLeadingZeroes) {
    long long current = apply(lhs, rhs, pending);
    char op = chooseBinaryOp(current);
    int nextRhs = chooseOperand(op, current);
    long long next = apply(current, nextRhs, op);
    while (next < kIntMin || next > kIntMax || (op == 'U' && nextRhs == 0)) {
        op = chooseBinaryOp(current);
        nextRhs = chooseOperand(op, current);
        next = apply(current, nextRhs, op);
    }

    expr += op;
    expr += numberText(nextRhs, allowLeadingZeroes);
    ++alphabetCount;

    lhs = current;
    rhs = nextRhs;
    pending = op;
    readingRhs = true;
}

void appendC(string& expr, int& alphabetCount, long long& lhs, long long& rhs,
             char& pending,
             bool& readingRhs) {
    lhs = apply(lhs, rhs, pending);
    expr += 'C';
    ++alphabetCount;
    rhs = 0;
    pending = 0;
    readingRhs = false;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int targetAlphabetCount = rnd.next(1, 18);
    if (mode == 4) {
        targetAlphabetCount = rnd.next(35, 120);
    }

    bool allowLeadingZeroes = mode == 1 || rnd.next(2) == 0;
    long long lhs = mode == 2 ? rnd.next(1000000000, 2147483647) : rnd.next(0, 1000);
    string expr = numberText(static_cast<int>(lhs), allowLeadingZeroes);

    int alphabetCount = 0;
    long long rhs = 0;
    char pending = 0;
    bool readingRhs = false;

    while (alphabetCount + 1 < targetAlphabetCount) {
        bool canClose = !readingRhs || pending == 0;
        if (canClose && (mode == 3 || rnd.next(100) < 35)) {
            appendC(expr, alphabetCount, lhs, rhs, pending, readingRhs);
        } else {
            appendBinary(expr, alphabetCount, lhs, rhs, pending, readingRhs, allowLeadingZeroes);
        }
    }

    if (readingRhs) {
        appendC(expr, alphabetCount, lhs, rhs, pending, readingRhs);
    } else if (rnd.next(3) == 0) {
        appendC(expr, alphabetCount, lhs, rhs, pending, readingRhs);
    } else {
        char op = chooseBinaryOp(lhs);
        expr += op;
        ++alphabetCount;
    }

    println(alphabetCount);
    println(expr);
    return 0;
}
