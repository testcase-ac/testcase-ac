#include "testlib.h"
using namespace std;

void generateTest(int type) {
    int n, t;
    vector<int> hp;
    vector<pair<int, int>> edges;

    if (type == 1) {
        // Simple path
        n = rnd.next(2, 10);
        t = rnd.next(2, n);
        hp.assign(n + 1, 0);

        hp[1] = rnd.next(0, 5);
        for (int i = 2; i <= n; ++i) {
            hp[i] = rnd.next(-5, 5);
        }

        // Ensure not all zero
        bool allZero = true;
        for (int i = 1; i <= n; ++i)
            if (hp[i] != 0) allZero = false;
        if (allZero) {
            int idx = rnd.next(1, n);
            if (idx == 1) hp[1] = 1;
            else hp[idx] = (rnd.next(0, 1) ? 3 : -3);
        }

        for (int i = 1; i < n; ++i)
            edges.push_back({i, i + 1});
    } else if (type == 2) {
        // Star centered at 1
        n = rnd.next(3, 10);
        t = rnd.next(2, n);
        hp.assign(n + 1, 0);

        hp[1] = rnd.next(0, 5);
        for (int i = 2; i <= n; ++i)
            hp[i] = rnd.next(-5, 5);

        // Ensure some non-zero
        bool allZero = true;
        for (int i = 1; i <= n; ++i)
            if (hp[i] != 0) allZero = false;
        if (allZero) {
            int idx = rnd.next(2, n);
            hp[idx] = (rnd.next(0, 1) ? 4 : -4);
        }

        for (int i = 2; i <= n; ++i)
            edges.push_back({1, i});
    } else if (type == 3) {
        // Special "detour helps" pattern
        int extra = rnd.next(0, 3);
        n = 4 + extra;
        t = 3;
        hp.assign(n + 1, 0);

        hp[1] = 0;
        hp[2] = 0;
        hp[3] = -rnd.next(2, 4); // negative
        hp[4] = rnd.next(-hp[3] + 1, -hp[3] + 5); // positive enough

        for (int i = 5; i <= n; ++i) {
            hp[i] = rnd.next(-5, 5);
        }

        edges.push_back({1, 2});
        edges.push_back({2, 3});
        edges.push_back({2, 4});
        for (int i = 5; i <= n; ++i) {
            int parent = rnd.next(1, 4);
            edges.push_back({parent, i});
        }
    } else if (type == 4) {
        // Random tree
        n = rnd.next(5, 15);
        t = rnd.next(2, n);
        hp.assign(n + 1, 0);

        hp[1] = rnd.next(0, 5);
        for (int i = 2; i <= n; ++i)
            hp[i] = rnd.next(-7, 7);

        for (int i = 2; i <= n; ++i) {
            int parent = rnd.next(1, i - 1);
            edges.push_back({parent, i});
        }
    } else if (type == 5) {
        // Deep chain with alternating signs
        n = rnd.next(8, 15);
        t = rnd.next(2, n);
        hp.assign(n + 1, 0);

        hp[1] = rnd.next(0, 3);
        for (int i = 2; i <= n; ++i) {
            if (i % 2 == 0)
                hp[i] = rnd.next(-5, 0);
            else
                hp[i] = rnd.next(0, 5);
        }

        for (int i = 1; i < n; ++i)
            edges.push_back({i, i + 1});
    } else { // type == 6
        // Minimal case n = 2
        n = 2;
        t = 2;
        hp.assign(n + 1, 0);

        hp[1] = rnd.next(0, 5);
        int choice = rnd.next(0, 2);
        if (choice == 0)
            hp[2] = rnd.next(-5, -1);
        else if (choice == 1)
            hp[2] = 0;
        else
            hp[2] = rnd.next(1, 5);

        edges.push_back({1, 2});
    }

    // Shuffle edges for randomness
    shuffle(edges.begin(), edges.end());

    println(n, t);
    vector<int> vals;
    vals.reserve(n);
    for (int i = 1; i <= n; ++i) vals.push_back(hp[i]);
    println(vals);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 2);
    println(T);

    if (T == 1) {
        int type = rnd.next(1, 6);
        generateTest(type);
    } else {
        // Ensure at least one tricky "detour" test, plus one random
        generateTest(3);
        int type = rnd.next(1, 6);
        if (type == 3) type = 4; // force some variety
        generateTest(type);
    }

    return 0;
}
