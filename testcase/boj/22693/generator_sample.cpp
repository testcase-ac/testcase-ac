#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char digitChar(int value) {
    return value < 10 ? char('0' + value) : char('A' + value - 10);
}

string randomNumberInBase(int base, int minLen, int maxLen, int mode) {
    int len = rnd.next(minLen, maxLen);
    if (mode == 0) {
        return "0";
    }

    string result;
    result.reserve(len);

    int first = rnd.next(1, base - 1);
    if (mode == 2) {
        first = base - 1;
    }
    result.push_back(digitChar(first));

    for (int i = 1; i < len; ++i) {
        int digit = 0;
        if (mode == 1) {
            digit = rnd.next(0, min(base - 1, 3));
        } else if (mode == 2) {
            digit = base - 1;
        } else if (mode == 3) {
            digit = (i % 2 == 0) ? rnd.next(0, base - 1) : 0;
        } else {
            digit = rnd.next(0, base - 1);
        }
        result.push_back(digitChar(digit));
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> notableBases = {8, 9, 10, 12, 16, 25, 27, 32, 35, 36};
    int datasets = rnd.next(4, 12);

    for (int tc = 0; tc < datasets; ++tc) {
        int base;
        if (tc < (int)notableBases.size() && rnd.next(0, 2) != 0) {
            base = notableBases[tc];
        } else {
            base = rnd.next(8, 36);
        }

        int mode = rnd.next(0, 4);
        int minLen = 1;
        int maxLen = rnd.next(1, 6);
        if (mode == 2) {
            maxLen = rnd.next(8, 12);
        }
        if (mode == 3) {
            minLen = rnd.next(2, 4);
            maxLen = rnd.next(minLen, 12);
        }

        string m = randomNumberInBase(base, minLen, maxLen, mode);
        println(base, m);
    }

    println(0, 0);
    return 0;
}
