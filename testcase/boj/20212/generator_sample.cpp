#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Query {
    int type;
    int i;
    int j;
    int k;
};

int randomValue(const vector<int>& values) {
    return values[rnd.next(0, static_cast<int>(values.size()) - 1)];
}

pair<int, int> randomInterval(const vector<int>& coordinates) {
    int l = randomValue(coordinates);
    int r = randomValue(coordinates);
    if (l > r) swap(l, r);
    return {l, r};
}

int randomDelta(int mode) {
    if (mode == 0) return rnd.next(-5, 5);
    if (mode == 1) return rnd.next(-100000, 100000);

    vector<int> edge_values = {-100000, -1, 0, 1, 100000};
    return randomValue(edge_values);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(2, 24);
    int update_count = rnd.next(1, n - 1);

    vector<int> coordinates;
    if (mode == 0) {
        for (int x = 1; x <= 12; ++x) coordinates.push_back(x);
    } else if (mode == 1) {
        coordinates = {1, 2, 3, 7, 8, 15, 16, 31, 32, 100};
    } else if (mode == 2) {
        coordinates = {1, 2, 999999998, 999999999, 1000000000};
    } else {
        int base = rnd.next(1, 999999950);
        for (int d : {0, 1, 2, 10, 11, 40, 49}) coordinates.push_back(base + d);
    }

    vector<int> slots(n, 2);
    for (int idx = 0; idx < update_count; ++idx) slots[idx] = 1;
    shuffle(slots.begin(), slots.end());

    vector<Query> queries;
    queries.reserve(n);

    for (int slot : slots) {
        if (slot == 1) {
            auto [l, r] = randomInterval(coordinates);
            queries.push_back({1, l, r, randomDelta(mode)});
        } else {
            auto [l, r] = randomInterval(coordinates);
            int version;
            if (mode == 3 && rnd.next(0, 2) == 0) {
                version = update_count;
            } else {
                version = rnd.next(1, update_count);
            }
            queries.push_back({2, l, r, version});
        }
    }

    println(n);
    for (const Query& query : queries) {
        println(query.type, query.i, query.j, query.k);
    }

    return 0;
}
