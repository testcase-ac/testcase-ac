#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int boundedPositive(int hi) {
    return rnd.next(1, max(1, hi));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 2);
    int a = 0, b = 0, c = 0;

    if (mode == 0) {
        c = rnd.any(vector<int>{2, 3, 10, 100, 10000, rnd.next(2, 120)});
        b = boundedPositive(min(10000, c * c - 1));
    } else if (mode == 1) {
        c = rnd.any(vector<int>{2, 7, 11, 100, 10000, rnd.next(2, 120)});
        a = boundedPositive(min(10000, c * c - 1));
    } else {
        c = 0;
        int root = rnd.any(vector<int>{2, 10, 100, 141, rnd.next(2, 141)});
        int sum = root * root;
        a = rnd.next(max(1, sum - 10000), min(10000, sum - 1));
        b = sum - a;
    }

    println(a, b, c);
    return 0;
}
