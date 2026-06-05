#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 25);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = i + 1;
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = n - i;
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = i + 1;

        int swaps = rnd.next(1, n);
        for (int it = 0; it < swaps; ++it) {
            int l = rnd.next(0, n - 2);
            int r = rnd.next(l + 1, n - 1);
            reverse(a.begin() + l, a.begin() + r + 1);
        }
    } else {
        int blocks = rnd.next(2, 8);
        vector<int> sizes(blocks, 1);
        int extra = rnd.next(0, 22);
        for (int i = 0; i < extra; ++i) sizes[rnd.next(blocks)]++;

        for (int size : sizes) n += size;
        --n;

        int base = 1;
        for (int b = 0; b < blocks; ++b) {
            vector<int> block;
            for (int x = 0; x < sizes[b]; ++x) block.push_back(base + x);

            int style = rnd.next(0, 2);
            if (style == 0) {
                reverse(block.begin(), block.end());
            } else if (style == 1) {
                shuffle(block.begin(), block.end());
            }

            a.insert(a.end(), block.begin(), block.end());
            base += sizes[b];
        }
    }

    println(n);
    println(a);

    return 0;
}
