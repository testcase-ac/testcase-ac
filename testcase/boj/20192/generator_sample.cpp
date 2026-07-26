#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 20);
    int mode = rnd.next(0, 3);
    vector<int> a(n);
    int value = rnd.next(1, 20);

    for (int i = 0; i < n; ++i) {
        if (mode == 0)
            a[i] = rnd.next(1, 20);
        else if (mode == 1)
            a[i] = value += rnd.next(0, 3);
        else if (mode == 2)
            a[i] = value -= rnd.next(0, value - 1);
        else
            a[i] = value;
    }

    println(n);
    println(a);
}
