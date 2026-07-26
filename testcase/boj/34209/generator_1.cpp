#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long makeWeight(int mode, int node, int n, const vector<int>& subtreeSize) {
    if (mode == 0) return 0;
    if (mode == 1) return 1;
    if (mode == 2) return rnd.next(0, 10);
    if (mode == 3) return rnd.next(0, 1000000000);
    if (mode == 4) return subtreeSize[node];
    if (mode == 5) return node % 5 == 0 ? 0 : rnd.next(1, 1000);
    if (mode == 6) return rnd.next(0, 1) ? 1000000000LL : 0LL;
    return (long long)(n - node + 1) * rnd.next(0, 3);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) n = 2;
    else if (sizeMode == 1) n = rnd.next(3, 8);
    else if (sizeMode == 2) n = rnd.next(9, 25);
    else if (sizeMode == 3) n = rnd.next(26, 80);
    else if (sizeMode == 4) n = rnd.next(81, 180);
    else n = rnd.next(181, 350);

    int treeMode = rnd.next(0, 6);
    vector<int> parent(n + 1, 0);
    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (treeMode == 0) {
            parent[i] = i - 1;
        } else if (treeMode == 1) {
            parent[i] = 1;
        } else if (treeMode == 2) {
            parent[i] = i / 2;
        } else if (treeMode == 3) {
            parent[i] = max(1, i - rnd.next(1, min(i - 1, 8)));
        } else if (treeMode == 4) {
            int spine = max(2, n / 3);
            parent[i] = (i <= spine ? i - 1 : rnd.next(1, spine));
        } else if (treeMode == 5) {
            parent[i] = rnd.wnext(i - 1, -3) + 1;
        } else {
            parent[i] = rnd.wnext(i - 1, 3) + 1;
        }
        children[parent[i]].push_back(i);
    }

    vector<int> subtreeSize(n + 1, 1);
    for (int i = n; i >= 2; --i) {
        subtreeSize[parent[i]] += subtreeSize[i];
    }

    int kMode = rnd.next(0, 5);
    int k;
    if (kMode == 0) k = 1;
    else if (kMode == 1) k = n - 1;
    else if (kMode == 2) k = max(1, min(n - 1, rnd.next(1, 4)));
    else if (kMode == 3) k = rnd.next(1, n - 1);
    else if (kMode == 4) k = max(1, n / 2);
    else k = max(1, min(n - 1, (int)children[1].size() + rnd.next(0, 3)));

    int weightMode = rnd.next(0, 7);
    println(n, k);
    for (int i = 2; i <= n; ++i) {
        println(parent[i], makeWeight(weightMode, i, n, subtreeSize));
    }

    return 0;
}
