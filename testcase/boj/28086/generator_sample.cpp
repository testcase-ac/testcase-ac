#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

const long long LIMIT = 134217728LL;

string toOctal(long long value) {
    if (value == 0) {
        return "0";
    }

    bool negative = value < 0;
    if (negative) {
        value = -value;
    }

    string digits;
    while (value > 0) {
        digits.push_back(char('0' + value % 8));
        value /= 8;
    }
    reverse(digits.begin(), digits.end());

    if (negative) {
        return "-" + digits;
    }
    return digits;
}

long long randomMagnitude() {
    int mode = rnd.next(100);
    if (mode < 55) {
        return rnd.next(0, 64);
    }
    if (mode < 80) {
        return rnd.next(0, 4096);
    }

    vector<long long> edges = {
        0,
        1,
        7,
        8,
        63,
        64,
        4095,
        4096,
        LIMIT - 1,
        LIMIT,
    };
    return rnd.any(edges);
}

long long randomValue(bool allowNegative) {
    long long value = randomMagnitude();
    if (allowNegative && value != 0 && rnd.next(2) == 0) {
        value = -value;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<char> ops = {'+', '-', '*', '/'};
    char op = rnd.any(ops);

    long long a = randomValue(true);
    long long b;
    if (op == '+' || op == '-') {
        b = randomValue(false);
    } else {
        b = randomValue(true);
    }

    int mode = rnd.next(100);
    if (mode < 12) {
        a = rnd.any(vector<long long>{-LIMIT, -1, 0, 1, LIMIT});
        b = rnd.any(vector<long long>{0, 1, 7, 8, LIMIT});
        if (op == '*' || op == '/') {
            b = rnd.any(vector<long long>{-LIMIT, -8, -1, 0, 1, 8, LIMIT});
        }
    } else if (mode < 24) {
        op = '/';
        a = randomValue(true);
        b = 0;
    } else if (mode < 40) {
        op = rnd.any(vector<char>{'*', '/'});
        a = rnd.next(-64, 64);
        b = rnd.next(-64, 64);
    }

    if ((op == '+' || op == '-') && b < 0) {
        b = -b;
    }

    println(toOctal(a) + string(1, op) + toOctal(b));
    return 0;
}
