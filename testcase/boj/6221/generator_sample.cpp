#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 20);
    int base = (mode == 5 ? rnd.next(900000000, 999999000) : rnd.next(1, 200));
    int step = rnd.next(1, 9);

    vector<int> widths(n), breadths(n);
    for (int i = 0; i < n; ++i) widths[i] = base + i * step;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) breadths[i] = base + 1000 + i * step;
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) breadths[i] = base + 1000 + (n - 1 - i) * step;
    } else if (mode == 2) {
        iota(breadths.begin(), breadths.end(), base + 1000);
        shuffle(breadths.begin(), breadths.end());
    } else if (mode == 3) {
        int block = rnd.next(2, min(6, n));
        for (int i = 0; i < n; ++i) {
            int group = i / block;
            int offset = block - 1 - (i % block);
            breadths[i] = base + 1000 + group * block + offset;
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) breadths[i] = base + 1000 + i;
            else breadths[i] = base + 1000 + n + (n - i);
        }
    } else {
        for (int i = 0; i < n; ++i) breadths[i] = base - i;
    }

    vector<pair<int, int>> bales;
    for (int i = 0; i < n; ++i) bales.push_back({widths[i], breadths[i]});
    shuffle(bales.begin(), bales.end());

    println(n);
    for (auto bale : bales) println(bale.first, bale.second);

    return 0;
}
