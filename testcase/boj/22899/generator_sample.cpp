#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    int k;
    vector<int> author(n);
    vector<long long> cost(n);

    if (mode == 0) {
        k = rnd.next(1, n);
        fill(author.begin(), author.end(), 1);
    } else if (mode == 1) {
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) author[i] = i + 1;
    } else if (mode == 2) {
        k = rnd.next(max(1, n / 2), n);
        int heavy = rnd.next(1, n);
        int otherCount = rnd.next(1, min(n, 5));
        vector<int> others;
        for (int id = 1; id <= n; ++id) {
            if (id != heavy) others.push_back(id);
        }
        shuffle(others.begin(), others.end());
        others.resize(min(otherCount, (int)others.size()));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 65 || others.empty()) {
                author[i] = heavy;
            } else {
                author[i] = rnd.any(others);
            }
        }
    } else if (mode == 3) {
        k = rnd.next(1, n);
        int authorCount = rnd.next(1, min(n, 7));
        for (int i = 0; i < n; ++i) author[i] = rnd.next(1, authorCount);
    } else if (mode == 4) {
        k = rnd.next(1, n);
        int blockSize = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < n; ++i) {
            author[i] = min(n, i / blockSize + 1);
        }
        shuffle(author.begin(), author.end());
    } else {
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) author[i] = rnd.next(1, n);
    }

    int costMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        if (costMode == 0) {
            cost[i] = rnd.next(1, 30);
        } else if (costMode == 1) {
            cost[i] = 1000000000LL - rnd.next(0, 50);
        } else if (costMode == 2) {
            cost[i] = (i % 3 == 0) ? rnd.next(1, 10) : rnd.next(900000000, 1000000000);
        } else {
            cost[i] = rnd.next(1, 1000000000);
        }
    }

    if (rnd.next(2)) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        vector<int> shuffledAuthor(n);
        vector<long long> shuffledCost(n);
        for (int i = 0; i < n; ++i) {
            shuffledAuthor[i] = author[order[i]];
            shuffledCost[i] = cost[order[i]];
        }
        author = shuffledAuthor;
        cost = shuffledCost;
    }

    println(n, k);
    println(author);
    println(cost);

    return 0;
}
