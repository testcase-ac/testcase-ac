#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 20);
    int mode = rnd.next(0, 4);
    vector<int> a(n);

    if (mode == 0) {
        for (int& x : a) x = rnd.next(1, n);
    } else if (mode == 1) {
        int values = rnd.next(1, std::min(n, 5));
        for (int& x : a) x = rnd.next(1, values);
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = i % 2 == 0 ? n : 1;
    } else {
        iota(a.begin(), a.end(), 1);
        if (mode == 3) reverse(a.begin(), a.end());
    }

    println(n);
    println(a);
}
