#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Query {
    int type;
    int dy;
    int dx;
    int y;
    int x;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 1;
    int m = 1;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = 1;
    } else {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
    }

    int maxQueries = rnd.next(8, 45);
    vector<Query> queries;

    auto addCut = [&](int dy, int dx, int y, int x) {
        queries.push_back({1, dy, dx, y, x});
    };
    auto addCell = [&](int y, int x) {
        queries.push_back({2, 0, 0, y, x});
    };
    auto addCount = [&]() {
        queries.push_back({3, 0, 0, 0, 0});
    };

    addCount();

    if (mode == 0) {
        addCell(1, rnd.next(1, m));
        addCut(0, rnd.any(vector<int>{-1, 1}), 1, rnd.next(1, m));
    } else if (mode == 1) {
        addCell(rnd.next(1, n), 1);
        addCut(rnd.any(vector<int>{-1, 1}), 0, rnd.next(1, n), 1);
    } else if (mode == 2) {
        int row = rnd.next(1, n);
        int col = rnd.next(1, m);
        addCut(0, 1, row, 1);
        addCut(1, 0, 1, col);
    } else if (mode == 3) {
        int row = rnd.next(1, n);
        int col = rnd.next(1, m);
        addCut(0, -1, row, m);
        addCut(-1, 0, n, col);
    } else {
        int y = rnd.next(1, n);
        int x = rnd.next(1, m);
        addCut(0, 1, y, max(1, x - 1));
        addCut(0, -1, y, min(m, x + 1));
        addCut(1, 0, max(1, y - 1), x);
        addCut(-1, 0, min(n, y + 1), x);
    }

    while ((int)queries.size() < maxQueries) {
        int choice = rnd.next(0, 99);
        if (choice < 55) {
            int dir = rnd.next(0, 3);
            int y = rnd.next(1, n);
            int x = rnd.next(1, m);
            if (dir == 0) addCut(-1, 0, y, x);
            if (dir == 1) addCut(1, 0, y, x);
            if (dir == 2) addCut(0, -1, y, x);
            if (dir == 3) addCut(0, 1, y, x);
        } else if (choice < 85) {
            addCell(rnd.next(1, n), rnd.next(1, m));
        } else {
            addCount();
        }
    }

    println(n, m, (int)queries.size());
    for (const Query& q : queries) {
        if (q.type == 1) {
            println(q.type, q.dy, q.dx, q.y, q.x);
        } else if (q.type == 2) {
            println(q.type, q.y, q.x);
        } else {
            println(q.type);
        }
    }

    return 0;
}
