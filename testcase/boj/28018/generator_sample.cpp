#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampTime(int value) {
    return max(0, min(1000000, value));
}

void addQuery(vector<int>& queries, int value) {
    queries.push_back(clampTime(value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 16);
    vector<pair<int, int>> intervals;

    if (mode == 0) {
        int base = rnd.next(1, 40);
        for (int i = 0; i < n; ++i) {
            int s = base + rnd.next(0, 8);
            int e = s + rnd.next(0, 12);
            intervals.emplace_back(s, e);
        }
    } else if (mode == 1) {
        int pivot = rnd.next(2, 999998);
        for (int i = 0; i < n; ++i) {
            int width = rnd.next(0, 10);
            int s = max(1, pivot - rnd.next(0, width + 3));
            int e = min(1000000, pivot + rnd.next(0, width + 3));
            intervals.emplace_back(s, e);
        }
    } else if (mode == 2) {
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int s = cur;
            int e = s + rnd.next(0, 4);
            intervals.emplace_back(s, e);
            cur = e + rnd.next(1, 5);
        }
    } else if (mode == 3) {
        vector<pair<int, int>> edgeCases = {
            {1, 1},
            {1, rnd.next(1, 8)},
            {rnd.next(999990, 1000000), 1000000},
            {1000000, 1000000},
        };
        shuffle(edgeCases.begin(), edgeCases.end());
        for (auto interval : edgeCases) intervals.push_back(interval);
        while ((int)intervals.size() < n) {
            int s = rnd.next(1, 1000000);
            intervals.emplace_back(s, min(1000000, s + rnd.next(0, 5)));
        }
    } else {
        int left = rnd.next(1, 999980);
        int right = left + rnd.next(10, 20);
        intervals.emplace_back(left, right);
        while ((int)intervals.size() < n) {
            int s = rnd.next(left, right);
            int e = rnd.next(s, right);
            intervals.emplace_back(s, e);
        }
    }

    shuffle(intervals.begin(), intervals.end());

    int q = rnd.next(1, 24);
    vector<int> queries;
    queries.reserve(q);
    addQuery(queries, 0);
    addQuery(queries, 1000000);

    for (auto [s, e] : intervals) {
        if ((int)queries.size() >= q) break;
        int choice = rnd.next(0, 5);
        if (choice == 0) addQuery(queries, s - 1);
        else if (choice == 1) addQuery(queries, s);
        else if (choice == 2) addQuery(queries, (s + e) / 2);
        else if (choice == 3) addQuery(queries, e);
        else if (choice == 4) addQuery(queries, e + 1);
        else addQuery(queries, rnd.next(0, 1000000));
    }

    while ((int)queries.size() < q) {
        if (rnd.next(0, 3) == 0) {
            addQuery(queries, rnd.next(0, 1000000));
        } else {
            auto [s, e] = rnd.any(intervals);
            addQuery(queries, rnd.next(s, e));
        }
    }
    shuffle(queries.begin(), queries.end());

    println((int)intervals.size());
    for (auto [s, e] : intervals) println(s, e);
    println((int)queries.size());
    println(queries);

    return 0;
}
