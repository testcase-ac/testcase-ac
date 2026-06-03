#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 5) {
        n = rnd.next(80, 100);
    } else {
        n = rnd.next(4, 18);
    }

    vector<int> aPool;
    vector<int> bPool;
    for (int i = 1; i <= 500; ++i) {
        aPool.push_back(i);
        bPool.push_back(i);
    }
    shuffle(aPool.begin(), aPool.end());
    shuffle(bPool.begin(), bPool.end());

    vector<int> a(aPool.begin(), aPool.begin() + n);
    vector<int> b(bPool.begin(), bPool.begin() + n);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    if (mode == 1) {
        reverse(b.begin(), b.end());
    } else if (mode == 2) {
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            int left = rnd.next(0, n - 1);
            int right = rnd.next(0, n - 1);
            swap(b[left], b[right]);
        }
    } else if (mode == 3) {
        int block = rnd.next(2, min(n, 6));
        for (int start = 0; start < n; start += block) {
            int finish = min(n, start + block);
            reverse(b.begin() + start, b.begin() + finish);
        }
    } else if (mode == 4) {
        shuffle(b.begin(), b.end());
    } else if (mode == 5) {
        reverse(b.begin(), b.end());
        int swaps = rnd.next(3, 12);
        for (int i = 0; i < swaps; ++i) {
            int left = rnd.next(0, n - 1);
            int right = rnd.next(0, n - 1);
            swap(b[left], b[right]);
        }
    }

    vector<pair<int, int>> wires;
    for (int i = 0; i < n; ++i) {
        wires.emplace_back(a[i], b[i]);
    }

    if (rnd.next(0, 1) == 1) {
        shuffle(wires.begin(), wires.end());
    }

    println(n);
    for (const auto& wire : wires) {
        println(wire.first, wire.second);
    }

    return 0;
}
