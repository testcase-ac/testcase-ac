#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeParents(int n, int mode) {
    vector<int> parent(n + 1);
    parent[1] = 0;

    for (int i = 2; i <= n; ++i) {
        if (mode == 0) {
            parent[i] = i - 1;
        } else if (mode == 1) {
            parent[i] = 1;
        } else if (mode == 2) {
            parent[i] = i / 2;
        } else if (mode == 3) {
            parent[i] = max(1, i - rnd.next(1, min(i - 1, 3)));
        } else {
            parent[i] = rnd.next(1, i - 1);
        }
    }

    return parent;
}

int marbleCount(int mode) {
    if (mode == 0) return rnd.next(0, 1);
    if (mode == 1) return rnd.next(0, 8);
    if (mode == 2) return rnd.next(0, 20) * 2;
    if (mode == 3) return rnd.next(0, 20) * 2 + 1;
    if (mode == 4) return rnd.any(vector<int>{0, 1, 2, 999999, 1000000});
    return rnd.next(0, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int treeMode = tc < 5 ? tc : rnd.next(0, 4);
        int marbleMode = rnd.next(0, 5);
        int n;

        if (tc == 0) {
            n = 3;
        } else if (tc == 1) {
            n = rnd.next(4, 7);
        } else {
            n = rnd.next(3, 14);
        }

        vector<int> marbles(n);
        for (int& x : marbles) x = marbleCount(marbleMode);

        vector<int> parents = makeParents(n, treeMode);
        vector<int> outputParents;
        for (int i = 1; i <= n; ++i) outputParents.push_back(parents[i]);

        println(n);
        println(marbles);
        println(outputParents);
    }

    return 0;
}
