#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else {
        n = rnd.next(2, 60);
    }

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int swaps = rnd.next(1, min(n, 8));
        for (int i = 0; i < swaps; ++i) {
            int x = rnd.next(0, n - 1);
            int y = rnd.next(0, n - 1);
            swap(a[x], a[y]);
        }
    } else if (mode == 3) {
        vector<int> b;
        int l = 1, r = n;
        while (l <= r) {
            if (rnd.next(0, 1)) {
                b.push_back(l++);
                if (l <= r) {
                    b.push_back(r--);
                }
            } else {
                b.push_back(r--);
                if (l <= r) {
                    b.push_back(l++);
                }
            }
        }
        a = b;
    } else if (mode == 4) {
        vector<int> starts;
        for (int pos = 0; pos < n;) {
            starts.push_back(pos);
            pos += rnd.next(1, min(8, n - pos));
        }
        vector<vector<int>> blocks;
        for (int i = 0; i < (int)starts.size(); ++i) {
            int from = starts[i];
            int to = (i + 1 == (int)starts.size() ? n : starts[i + 1]);
            blocks.push_back(vector<int>(a.begin() + from, a.begin() + to));
        }
        shuffle(blocks.begin(), blocks.end());
        a.clear();
        for (const vector<int>& block : blocks) {
            a.insert(a.end(), block.begin(), block.end());
        }
    } else {
        int cut = rnd.next(1, n - 1);
        rotate(a.begin(), a.begin() + cut, a.end());
        if (n >= 4 && rnd.next(0, 1)) {
            reverse(a.begin(), a.begin() + rnd.next(2, n / 2));
        }
    }

    println(n);
    println(a);
    return 0;
}
