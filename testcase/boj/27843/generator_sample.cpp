#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 18);
    } else {
        n = rnd.next(19, 45);
    }

    long long scale = rnd.next(1, 20);
    int sign = rnd.next(0, 1) == 0 ? -1 : 1;

    vector<long long> a;
    long long value = scale;
    for (int i = 0; i < n; ++i) {
        a.push_back(sign * value);
        value *= 2;
    }

    if (mode != 0 && rnd.next(0, 2) != 0) {
        shuffle(a.begin(), a.end());
    } else if (rnd.next(0, 1) == 0) {
        reverse(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
