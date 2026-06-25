#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 40);

    if (mode == 5) n = rnd.next(40, 120);

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        // Strictly increasing.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        vector<int> low, high;
        for (int x = 1; x <= n; ++x) {
            if (x <= n / 2) low.push_back(x);
            else high.push_back(x);
        }
        shuffle(low.begin(), low.end());
        shuffle(high.begin(), high.end());

        a.clear();
        while (!high.empty() || !low.empty()) {
            if (!high.empty()) {
                a.push_back(high.back());
                high.pop_back();
            }
            if (!low.empty()) {
                a.push_back(low.back());
                low.pop_back();
            }
        }
    } else if (mode == 4) {
        int peak = rnd.next(0, n - 1);
        a.erase(a.begin() + (n - 1));
        shuffle(a.begin(), a.end());
        a.insert(a.begin() + peak, n);
    } else if (mode == 5) {
        int swaps = rnd.next(1, n / 3);
        for (int i = 0; i < swaps; ++i) {
            int left = rnd.next(0, n - 2);
            int right = rnd.next(left + 1, min(n - 1, left + 5));
            swap(a[left], a[right]);
        }
    } else {
        int cut = rnd.next(1, n - 1);
        reverse(a.begin(), a.begin() + cut);
        shuffle(a.begin() + cut, a.end());
    }

    println(n);
    for (int x : a) println(x);

    return 0;
}
