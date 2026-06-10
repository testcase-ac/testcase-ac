#include "testlib.h"
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

using Query = pair<int, int>;

int halfSum(const vector<int>& a, int l, int r) {
    return accumulate(a.begin() + l, a.begin() + r, 0);
}

void appendValue(vector<Query>& queries, vector<int>& a, int lo, int hi) {
    int x = rnd.next(lo, hi);
    queries.push_back({1, x});
    a.push_back(x);
}

void appendCut(vector<Query>& queries, vector<int>& a) {
    queries.push_back({2, 0});

    int n = int(a.size());
    int mid = n / 2;
    int front = halfSum(a, 0, mid);
    int back = halfSum(a, mid, n);

    if (front <= back) {
        a.erase(a.begin(), a.begin() + mid);
    } else {
        a.erase(a.begin() + mid, a.end());
    }
}

void emitQueries(const vector<Query>& queries) {
    println(int(queries.size()));
    for (Query q : queries) {
        if (q.first == 1) {
            println(1, q.second);
        } else {
            println(2);
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Query> queries;
    vector<int> a;

    int mode = rnd.next(0, 4);
    int targetQ = rnd.next(8, 60);

    if (mode == 0) {
        int pairs = rnd.next(2, 8);
        for (int i = 0; i < pairs; ++i) {
            int x = rnd.next(1, 25);
            appendValue(queries, a, x, x);
            appendValue(queries, a, x, x);
        }
        while (queries.size() < size_t(targetQ)) {
            if (a.size() >= 2 && rnd.next(0, 2) == 0) {
                appendCut(queries, a);
            } else {
                appendValue(queries, a, 1, 40);
            }
        }
    } else if (mode == 1) {
        int blocks = rnd.next(2, 6);
        for (int b = 0; b < blocks; ++b) {
            int small = rnd.next(1, 8);
            int large = rnd.next(30, 80);
            int len = rnd.next(2, 7);
            for (int i = 0; i < len; ++i) appendValue(queries, a, small, small + 2);
            for (int i = 0; i < len + rnd.next(0, 2); ++i) appendValue(queries, a, large, large + 10);
            if (a.size() >= 2) appendCut(queries, a);
        }
    } else if (mode == 2) {
        int blocks = rnd.next(2, 6);
        for (int b = 0; b < blocks; ++b) {
            int large = rnd.next(30, 90);
            int small = rnd.next(1, 7);
            int len = rnd.next(2, 7);
            for (int i = 0; i < len + rnd.next(0, 2); ++i) appendValue(queries, a, large, large + 10);
            for (int i = 0; i < len; ++i) appendValue(queries, a, small, small + 2);
            if (a.size() >= 2) appendCut(queries, a);
        }
    } else if (mode == 3) {
        int rounds = rnd.next(3, 10);
        for (int r = 0; r < rounds; ++r) {
            int add = rnd.next(2, 8);
            for (int i = 0; i < add; ++i) {
                int lo = (r % 2 == 0 ? 1 : 20);
                int hi = (r % 2 == 0 ? 60 : 100);
                appendValue(queries, a, lo, hi);
            }
            while (a.size() >= 2 && rnd.next(0, 2) != 0) appendCut(queries, a);
        }
    } else {
        while (queries.size() < size_t(targetQ)) {
            if (a.size() >= 2 && rnd.next(0, 99) < 35) {
                appendCut(queries, a);
            } else {
                int hi = rnd.next(0, 99) < 15 ? 1000 : 120;
                appendValue(queries, a, 1, hi);
            }
        }
    }

    while (queries.size() < 3) appendValue(queries, a, 1, 10);
    bool hasCut = false;
    for (Query q : queries) hasCut |= q.first == 2;
    while (!hasCut) {
        appendValue(queries, a, 1, 10);
        if (a.size() >= 2) {
            appendCut(queries, a);
            hasCut = true;
        }
    }

    if (queries.size() > 500000) queries.resize(500000);
    emitQueries(queries);

    return 0;
}
