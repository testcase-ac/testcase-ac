#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 18);
    if (mode == 1) n = rnd.next(2, 18);
    if (mode == 2) n = rnd.next(3, 18);
    if (mode == 4) n = rnd.next(2, 18);

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        // Identity shuffle.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int shift = rnd.next(1, n - 1);
        for (int i = 0; i < n; ++i) a[i] = (i + shift) % n + 1;
    } else if (mode == 3) {
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        for (int i = 0; i + 1 < n; i += 2) {
            if (rnd.next(0, 1)) swap(a[i], a[i + 1]);
        }
        if (is_sorted(a.begin(), a.end())) swap(a[0], a[1]);
    } else if (mode == 5) {
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            int x = rnd.next(0, n - 1);
            int y = rnd.next(0, n - 1);
            swap(a[x], a[y]);
        }
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end());
        int first = order[0];
        for (int i = 0; i + 1 < n; ++i) a[order[i]] = order[i + 1] + 1;
        a[order.back()] = first + 1;
    }

    vector<int> ids;
    set<int> used;
    int idMode = rnd.next(0, 4);
    while ((int)ids.size() < n) {
        int id;
        if (idMode == 0) {
            id = 1000000 + (int)ids.size() * rnd.next(1, 17) + rnd.next(0, 9);
        } else if (idMode == 1) {
            id = 9999999 - (int)ids.size() * rnd.next(1, 23) - rnd.next(0, 9);
        } else if (idMode == 2) {
            id = rnd.next(1000000, 1000100);
        } else if (idMode == 3) {
            id = rnd.next(9999800, 9999999);
        } else {
            id = rnd.next(1000000, 9999999);
        }
        if (used.insert(id).second) ids.push_back(id);
    }

    if (rnd.next(0, 1)) shuffle(ids.begin(), ids.end());

    println(n);
    println(a);
    println(ids);

    return 0;
}
