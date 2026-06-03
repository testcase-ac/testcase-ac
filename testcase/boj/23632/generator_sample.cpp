#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> randomSet(int n, int count) {
    vector<int> values(n);
    iota(values.begin(), values.end(), 1);
    shuffle(values.begin(), values.end());
    values.resize(count);
    sort(values.begin(), values.end());
    return values;
}

vector<int> withRequired(int n, int count, int required) {
    vector<int> values;
    values.push_back(required);

    vector<int> rest;
    for (int i = 1; i <= n; ++i) {
        if (i != required) {
            rest.push_back(i);
        }
    }
    shuffle(rest.begin(), rest.end());
    while ((int)values.size() < count) {
        values.push_back(rest.back());
        rest.pop_back();
    }
    sort(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(4, 18);
    }

    int maxKinds = min(n, 30);
    int m = (mode == 0 ? 1 : rnd.next(1, n));
    int t = rnd.next(0, n);

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    vector<int> initial(order.begin(), order.begin() + m);
    vector<bool> built(n + 1, false);
    for (int building : initial) {
        built[building] = true;
    }

    vector<vector<int>> produces(n + 1);
    vector<vector<int>> requirements(n + 1);

    for (int building = 1; building <= n; ++building) {
        int count;
        if (mode == 2) {
            count = rnd.next(max(1, maxKinds / 2), maxKinds);
        } else {
            count = rnd.next(1, maxKinds);
        }

        int keyResource = building;
        if (mode == 1 && building < n) {
            keyResource = building + 1;
        } else if (mode == 3) {
            keyResource = rnd.next(1, n);
        }
        produces[building] = withRequired(n, count, keyResource);
    }

    for (int building = 1; building <= n; ++building) {
        if (built[building]) {
            continue;
        }

        int count;
        if (mode == 2) {
            count = rnd.next(max(1, maxKinds / 2), maxKinds);
        } else {
            count = rnd.next(1, maxKinds);
        }

        if (mode == 1) {
            int predecessor = max(1, building - 1);
            requirements[building] = withRequired(n, count, predecessor);
        } else if (mode == 4) {
            requirements[building] = withRequired(n, count, building);
        } else {
            requirements[building] = randomSet(n, count);
        }
    }

    println(n, m, t);
    println(initial);
    for (int building = 1; building <= n; ++building) {
        printf("%d", (int)produces[building].size());
        for (int resource : produces[building]) {
            printf(" %d", resource);
        }
        printf("\n");
    }
    for (int building = 1; building <= n; ++building) {
        if (built[building]) {
            continue;
        }
        printf("%d %d", building, (int)requirements[building].size());
        for (int resource : requirements[building]) {
            printf(" %d", resource);
        }
        printf("\n");
    }

    return 0;
}
