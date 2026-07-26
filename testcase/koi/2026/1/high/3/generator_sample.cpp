#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 15);
    int mode = rnd.next(0, 3);
    int d = mode == 1 ? 1000000000 : rnd.next(1, 20);
    vector<int> x(n);

    for (int i = 0; i < n; ++i) {
        if (mode == 0)
            x[i] = rnd.next(1, 30);
        else if (mode == 1)
            x[i] = rnd.next(1, 1000000000);
        else if (mode == 2)
            x[i] = rnd.next(1, d + 1);
        else
            x[i] = rnd.next(0, 1) ? 1 : 1000000000;
    }

    println(n, d);
    println(x);
}
