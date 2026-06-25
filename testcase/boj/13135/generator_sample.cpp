#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode <= 2) {
        n = rnd.next(2, 8);
    } else if (mode <= 4) {
        n = rnd.next(9, 30);
    } else {
        n = rnd.next(31, 80);
    }

    vector<pair<int, int>> votes;
    votes.reserve(n);

    for (int i = 0; i < n; ++i) {
        int total;
        if (mode == 0) {
            total = rnd.next(1, 12);
        } else if (mode == 1) {
            total = rnd.any(vector<int>{1, 2, 99998, 99999, 100000});
        } else if (mode == 2) {
            total = rnd.next(50000, 100000);
        } else if (mode == 3) {
            total = rnd.next(1, 100000);
        } else if (mode == 4) {
            total = rnd.next(90000, 100000);
        } else if (mode == 5) {
            total = rnd.next(1, 2000);
        } else {
            total = rnd.next(1, 100000);
        }

        int a;
        if (mode == 0) {
            a = rnd.next(0, total);
        } else if (mode == 1) {
            a = rnd.any(vector<int>{0, total, total / 2});
        } else if (mode == 2) {
            int shift = rnd.next(-5, 5);
            a = max(0, min(total, total / 2 + shift));
        } else if (mode == 3) {
            a = rnd.next(0, min(total, 20));
        } else if (mode == 4) {
            a = rnd.next(max(0, total - 20), total);
        } else if (mode == 5) {
            a = rnd.next(0, total);
        } else {
            a = rnd.next(0, total);
        }
        votes.push_back({a, total - a});
    }

    long long sumA = 0;
    long long sumB = 0;
    for (auto [a, b] : votes) {
        sumA += a;
        sumB += b;
    }

    while (sumB <= sumA) {
        vector<int> candidates;
        for (int i = 0; i < n; ++i) {
            if (votes[i].first > 0) {
                candidates.push_back(i);
            }
        }
        int idx = rnd.any(candidates);
        --votes[idx].first;
        ++votes[idx].second;
        --sumA;
        ++sumB;
    }

    shuffle(votes.begin(), votes.end());

    println(n);
    for (auto [a, b] : votes) {
        println(a, b);
    }

    return 0;
}
