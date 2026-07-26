#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> makeDisjoint(int n) {
    vector<pair<int, int>> pairs;
    for (int i = 0; i < n; ++i) {
        pairs.push_back({2 * i + 1, 2 * i + 2});
    }
    return pairs;
}

vector<pair<int, int>> makeNested(int n) {
    vector<pair<int, int>> pairs;
    for (int i = 1; i <= n; ++i) {
        pairs.push_back({i, 2 * n + 1 - i});
    }
    return pairs;
}

vector<pair<int, int>> makeDyck(int n, int mode) {
    vector<pair<int, int>> pairs;
    vector<int> st;
    int opened = 0;
    for (int pos = 1; pos <= 2 * n; ++pos) {
        bool open;
        if (opened == n) {
            open = false;
        } else if (st.empty()) {
            open = true;
        } else if (mode == 0) {
            open = rnd.next(0, 99) < 70;
        } else if (mode == 1) {
            open = rnd.next(0, 99) < 35;
        } else {
            open = rnd.next(0, 1) == 0;
        }

        if (open) {
            st.push_back(pos);
            ++opened;
        } else {
            pairs.push_back({st.back(), pos});
            st.pop_back();
        }
    }
    return pairs;
}

vector<pair<int, int>> makeBlocks(int n) {
    vector<pair<int, int>> pairs;
    int pos = 1;
    int remaining = n;
    while (remaining > 0) {
        int block = rnd.next(1, min(remaining, rnd.next(1, 8)));
        vector<pair<int, int>> local = rnd.next(0, 1) ? makeNested(block) : makeDyck(block, rnd.next(0, 2));
        for (auto [l, r] : local) {
            pairs.push_back({l + pos - 1, r + pos - 1});
        }
        pos += 2 * block;
        remaining -= block;
    }
    return pairs;
}

void reorderPairs(vector<pair<int, int>>& pairs, int mode) {
    if (mode == 0) {
        sort(pairs.begin(), pairs.end());
    } else if (mode == 1) {
        sort(pairs.rbegin(), pairs.rend());
    } else if (mode == 2) {
        sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    } else {
        shuffle(pairs.begin(), pairs.end());
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int totalMode = rnd.next(0, 4);
    int totalN;
    if (totalMode == 0) totalN = 1;
    else if (totalMode == 1) totalN = rnd.next(2, 20);
    else if (totalMode == 2) totalN = rnd.next(21, 60);
    else if (totalMode == 3) totalN = rnd.next(61, 120);
    else totalN = rnd.next(121, 240);

    int t = rnd.next(1, min(20, totalN));
    vector<int> ns;
    int remaining = totalN;
    for (int i = 0; i < t; ++i) {
        int left = t - i - 1;
        int n = (i == t - 1) ? remaining : rnd.next(1, remaining - left);
        ns.push_back(n);
        remaining -= n;
    }
    shuffle(ns.begin(), ns.end());

    println(t);
    for (int idx = 0; idx < t; ++idx) {
        int n = ns[idx];
        int mode = (idx + rnd.next(0, 4)) % 5;

        vector<pair<int, int>> pairs;
        if (mode == 0) pairs = makeDisjoint(n);
        else if (mode == 1) pairs = makeNested(n);
        else if (mode == 2) pairs = makeDyck(n, 0);
        else if (mode == 3) pairs = makeDyck(n, 1);
        else pairs = makeBlocks(n);

        reorderPairs(pairs, rnd.next(0, 3));
        println(n);
        for (auto [l, r] : pairs) {
            println(l, r);
        }
    }
    return 0;
}
