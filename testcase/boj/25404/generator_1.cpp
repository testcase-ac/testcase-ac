#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 20);
    int mode = rnd.next(0, 3);
    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(1, 1000000000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int first = rnd.next(1, 1000000001 - n);
        for (int i = 0; i < n; ++i) a[i] = first + i;
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        int kinds = rnd.next(1, n);
        for (int& value : a) value = rnd.next(1, kinds);
    } else {
        for (int& value : a) value = rnd.next(1, 1000000000);
    }

    println(n);
    println(a);
}
