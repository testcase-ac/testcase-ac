#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

vector<int> makeDistinctPositions(int n, int mode) {
    set<int> xs;

    if (mode == 0) {
        xs.insert(0);
        xs.insert(1000000000);
    }

    int base = rnd.next(0, 1000000000 - 4 * n);
    int step = rnd.next(1, 9);
    for (int i = 0; (int)xs.size() < n && i < n * 3; ++i) {
        int noise = rnd.next(0, 2);
        xs.insert(base + i * step + noise);
    }

    while ((int)xs.size() < n) {
        xs.insert(rnd.next(0, 1000000000));
    }

    vector<int> result(xs.begin(), xs.end());
    shuffle(result.begin(), result.end());
    result.resize(n);
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 18);
    if (mode == 0) n = 2;
    if (mode == 3) n = rnd.next(10, 30);

    vector<int> xs = makeDistinctPositions(n, mode);
    sort(xs.begin(), xs.end());

    vector<pair<int, int>> cows;
    cows.reserve(n);

    for (int i = 0; i < n; ++i) {
        int breed = rnd.next(0, 1);
        if (mode == 1) breed = i % 2;
        if (mode == 2) breed = (i < n / 2 ? 0 : 1);
        if (mode == 3) breed = (i == rnd.next(0, n - 1) ? 1 : 0);
        cows.push_back({breed, xs[i]});
    }

    cows[0].first = 0;
    cows[n - 1].first = 1;

    if (rnd.next(0, 1)) {
        shuffle(cows.begin(), cows.end());
    }

    println(n);
    for (const auto& cow : cows) {
        println(cow.first, cow.second);
    }

    return 0;
}
