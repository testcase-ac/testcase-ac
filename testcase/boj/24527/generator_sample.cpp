#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

long long triangular(long long x) {
    return x * (x + 1) / 2;
}

long long startAtRowColumn(int row, int column) {
    return triangular(row - 1) + column;
}

pair<int, int> intervalForStart(int h, long long a) {
    int row = 1;
    while (triangular(row) < a) row++;
    int start = int(a - triangular(row - 1));
    int len = h + 1 - row;
    return {start, start + len};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h;
    if (mode == 0) {
        h = rnd.next(1, 3);
    } else if (mode == 1) {
        h = rnd.next(4, 12);
    } else if (mode == 2) {
        h = rnd.next(15, 45);
    } else if (mode == 3) {
        h = rnd.next(90000, 100000);
    } else {
        h = rnd.next(2, 25);
    }

    int q = mode == 3 ? rnd.next(1, 8) : rnd.next(1, 18);
    int r = mode == 3 ? rnd.next(1, 8) : rnd.next(1, 18);
    long long maxStart = triangular(h);

    vector<pair<long long, int>> drops;
    vector<pair<int, int>> usefulIntervals;

    for (int i = 0; i < q; ++i) {
        long long a;
        if (mode == 0) {
            a = rnd.next(1LL, maxStart);
        } else if (mode == 1) {
            int row = rnd.next(1, h);
            int column = rnd.next(1, row);
            if (rnd.next(0, 3) == 0) column = 1;
            if (rnd.next(0, 3) == 0) column = row;
            a = startAtRowColumn(row, column);
        } else if (mode == 2) {
            int row = rnd.next(1, h);
            int choice = rnd.next(0, 4);
            if (choice == 0) a = startAtRowColumn(row, 1);
            else if (choice == 1) a = startAtRowColumn(row, row);
            else if (choice == 2) a = triangular(row);
            else a = startAtRowColumn(row, rnd.next(1, row));
        } else if (mode == 3) {
            int row = rnd.next(1, h);
            if (rnd.next(0, 4) == 0) row = rnd.any(vector<int>{1, h / 2, h});
            int column = rnd.next(1, row);
            a = startAtRowColumn(row, column);
        } else {
            a = rnd.next(1LL, maxStart);
        }

        int b;
        if (rnd.next(0, 5) == 0) b = 100000;
        else if (mode == 0) b = rnd.next(1, 20);
        else b = rnd.next(1, 1000);

        drops.push_back({a, b});
        usefulIntervals.push_back(intervalForStart(h, a));
    }

    vector<pair<int, int>> queries;
    for (int i = 0; i < r; ++i) {
        int a, b;
        int choice = rnd.next(0, 5);
        if (!usefulIntervals.empty() && choice <= 1) {
            auto base = rnd.any(usefulIntervals);
            a = max(1, base.first - rnd.next(0, 2));
            b = min(h + 1, base.second + rnd.next(0, 2));
        } else if (choice == 2) {
            a = 1;
            b = h + 1;
        } else if (choice == 3) {
            a = rnd.next(1, h + 1);
            b = a;
        } else {
            a = rnd.next(1, h + 1);
            b = rnd.next(a, h + 1);
        }
        queries.push_back({a, b});
    }

    shuffle(drops.begin(), drops.end());
    shuffle(queries.begin(), queries.end());

    println(h);
    println(q, r);
    for (auto drop : drops) println(drop.first, drop.second);
    for (auto query : queries) println(query.first, query.second);

    return 0;
}
