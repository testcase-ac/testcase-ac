#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int targetM = rnd.next(1, 80);
    vector<int> a;
    int sum = 0;

    while (sum < targetM) {
        int remaining = targetM - sum;
        int value;

        if (mode == 0) {
            value = 1;
        } else if (mode == 1) {
            value = rnd.next(1, min(remaining, 3));
        } else if (mode == 2) {
            value = rnd.next(1, remaining);
        } else if (mode == 3) {
            value = rnd.wnext(remaining, 3) + 1;
        } else if (mode == 4) {
            value = rnd.wnext(remaining, -3) + 1;
        } else {
            value = rnd.next(1, min(remaining, 12));
        }

        a.push_back(value);
        sum += value;
    }

    vector<int> b;
    for (int value : a) {
        for (int i = 0; i < value; ++i) {
            b.push_back(value);
        }
    }

    println((int)b.size());
    println(b);

    return 0;
}
