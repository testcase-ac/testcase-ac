#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;
    vector<pair<int, int>> statues;

    if (mode == 0) {
        n = rnd.next(1, 4);
        k = rnd.next(1, n);
        for (int i = 0; i < k; ++i) {
            statues.push_back({rnd.next(1, n), rnd.next(1, 9)});
        }
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        k = n;
        for (int i = 1; i <= k; ++i) {
            statues.push_back({i, k - i + 1});
        }
        int swaps = rnd.next(0, 3);
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, k - 1);
            int b = rnd.next(0, k - 1);
            swap(statues[a].second, statues[b].second);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 25);
        k = rnd.next(2, n);
        int sharedPosition = rnd.next(1, n);
        for (int i = 0; i < k; ++i) {
            int position = rnd.next(0, 2) == 0 ? sharedPosition : rnd.next(1, n);
            int size = rnd.next(1, 20);
            statues.push_back({position, size});
        }
    } else if (mode == 3) {
        n = rnd.next(6, 30);
        k = rnd.next(2, n);
        int sharedSize = rnd.next(1, 100);
        for (int i = 0; i < k; ++i) {
            int size = rnd.next(0, 3) == 0 ? rnd.next(1, 100) : sharedSize;
            statues.push_back({rnd.next(1, n), size});
        }
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        k = rnd.next(2, min(n, 15));
        for (int i = 0; i < k; ++i) {
            int position = rnd.next(0, 1) == 0 ? rnd.next(1, min(n, 5)) : rnd.next(max(1, n - 4), n);
            int size = rnd.next(1, 1000000);
            statues.push_back({position, size});
        }
    } else if (mode == 5) {
        n = rnd.next(30, 120);
        k = rnd.next(n / 2, n);
        for (int i = 0; i < k; ++i) {
            int position = rnd.next(1, n);
            int size = rnd.next(0, 1) == 0 ? rnd.next(1, 1000) : rnd.next(999000, 1000000);
            statues.push_back({position, size});
        }
    } else {
        n = rnd.next(2, 18);
        k = rnd.next(1, n);
        vector<int> positions;
        for (int i = 1; i <= n; ++i) positions.push_back(i);
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < k; ++i) {
            int size = (i + 1) * rnd.next(1, 7);
            statues.push_back({positions[i], size});
        }
        shuffle(statues.begin(), statues.end());
    }

    println(n, k);
    for (const auto& statue : statues) {
        println(statue.first, statue.second);
    }

    return 0;
}
