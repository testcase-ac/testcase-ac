#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeCase(int mode) {
    int n;
    vector<int> digits;

    if (mode == 0) {
        n = rnd.next(2, 5);
        digits.push_back(rnd.next(1, 9));
        digits.push_back(rnd.next(1, 9));
        while ((int)digits.size() < n) {
            digits.push_back(rnd.next(1, 9));
        }
    } else if (mode == 1) {
        n = rnd.next(3, 14);
        digits.push_back(rnd.next(1, 9));
        digits.push_back(rnd.next(1, 9));
        while ((int)digits.size() < n) {
            digits.push_back(rnd.next(0, 1) == 0 ? 0 : rnd.next(1, 9));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 14);
        int repeated = rnd.next(1, 9);
        int nonzeroCount = rnd.next(2, n);
        for (int i = 0; i < nonzeroCount; ++i) {
            digits.push_back(rnd.next(0, 3) == 0 ? rnd.next(1, 9) : repeated);
        }
        while ((int)digits.size() < n) {
            digits.push_back(0);
        }
    } else {
        n = 14;
        digits = {0, 0, 0, 0, 0, 0, 1, 2};
        while ((int)digits.size() < n) {
            digits.push_back(rnd.next(3, 9));
        }
    }

    shuffle(digits.begin(), digits.end());
    return digits;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(1, 8);
    for (int tc = 0; tc < caseCount; ++tc) {
        vector<int> digits = makeCase(rnd.next(0, 3));
        printf("%d", (int)digits.size());
        for (int digit : digits) {
            printf(" %d", digit);
        }
        printf("\n");
    }
    println(0);

    return 0;
}
