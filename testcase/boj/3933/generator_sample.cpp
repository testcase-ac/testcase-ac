#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static int positiveSquareSum(int terms) {
    int remaining = 32767;
    int sum = 0;
    for (int i = 0; i < terms; ++i) {
        int maxRoot = 1;
        while ((maxRoot + 1) * (maxRoot + 1) <= remaining - (terms - i - 1)) {
            ++maxRoot;
        }
        int root = rnd.next(1, maxRoot);
        sum += root * root;
        remaining -= root * root;
    }
    return sum;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(8, 40);
    vector<int> values;
    values.reserve(testCases);

    while ((int)values.size() < testCases) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 0) {
            n = rnd.next(1, 30);
        } else if (mode == 1) {
            int root = rnd.next(1, 181);
            n = root * root;
        } else if (mode == 2) {
            n = positiveSquareSum(rnd.next(2, 4));
        } else if (mode == 3) {
            n = rnd.next(32700, 32767);
        } else if (mode == 4) {
            int root = rnd.next(1, 181);
            n = min(32767, root * root + rnd.next(1, 20));
        } else {
            n = rnd.next(1, 32767);
        }
        values.push_back(n);
    }

    shuffle(values.begin(), values.end());
    for (int n : values) {
        println(n);
    }
    println(0);

    return 0;
}
