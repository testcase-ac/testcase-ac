#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(20, 40);
    } else {
        n = rnd.next(5, 25);
    }

    vector<int> values;
    values.reserve(n);

    for (int i = 0; i < n; ++i) {
        int k;
        if (mode == 0) {
            k = rnd.next(10, 120);
        } else if (mode == 1) {
            k = rnd.next(10, 5000);
        } else if (mode == 2) {
            int offset = rnd.next(0, 100000);
            k = 2000000000 - offset;
        } else if (mode == 3) {
            int base = rnd.next(5, 1000000000);
            k = base * 2;
        } else {
            int base = rnd.next(5, 999999999);
            k = base * 2 + 1;
        }

        values.push_back(k);
    }

    println(n);
    for (int k : values) {
        println(k);
    }

    return 0;
}
