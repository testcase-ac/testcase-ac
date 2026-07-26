#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 20);
    int mode = rnd.next(0, 3);
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 2) {
        vector<int> zigzag;
        int lo = 1, hi = n;
        while (lo <= hi) {
            zigzag.push_back(lo++);
            if (lo <= hi) zigzag.push_back(hi--);
        }
        a = zigzag;
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else {
        for (int i = 0; i < rnd.next(1, 4); ++i)
            swap(a[rnd.next(0, n - 1)], a[rnd.next(0, n - 1)]);
    }

    println(n);
    println(a);
}
