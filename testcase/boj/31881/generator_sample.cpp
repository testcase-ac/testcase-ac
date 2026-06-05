#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Query {
    int type;
    int x;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int q;
    vector<Query> queries;

    if (mode == 0) {
        n = 1;
        q = rnd.next(1, 8);
        for (int i = 0; i < q - 1; ++i) {
            queries.push_back({rnd.next(1, 2), 1});
        }
        queries.push_back({3, 0});
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        q = rnd.next(5, 16);
        int x = rnd.next(1, n);
        for (int i = 0; i < q; ++i) {
            int type = (i % 4 == 3 ? 3 : rnd.next(1, 2));
            queries.push_back({type, type == 3 ? 0 : x});
        }
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        q = rnd.next(6, 20);
        vector<int> endpoints = {1, n};
        for (int i = 0; i < q; ++i) {
            int type = rnd.next(1, 5) == 5 ? 3 : rnd.next(1, 2);
            queries.push_back({type, type == 3 ? 0 : rnd.any(endpoints)});
        }
    } else if (mode == 3) {
        n = rnd.next(3, 30);
        q = rnd.next(8, 40);
        for (int i = 0; i < q; ++i) {
            int roll = rnd.next(1, 10);
            int type = roll <= 4 ? 1 : (roll <= 8 ? 2 : 3);
            queries.push_back({type, type == 3 ? 0 : rnd.next(1, n)});
        }
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        q = rnd.next(5, 24);
        for (int i = 0; i < q; ++i) {
            int type = rnd.next(1, 3) == 3 ? rnd.next(1, 2) : 3;
            queries.push_back({type, type == 3 ? 0 : rnd.next(1, n)});
        }
    } else {
        n = rnd.next(100000, 200000);
        q = rnd.next(5, 20);
        for (int i = 0; i < q; ++i) {
            int type = rnd.next(1, 6) == 6 ? 3 : rnd.next(1, 2);
            int x = rnd.next(0, 2) == 0 ? rnd.next(1, min(n, 5)) : rnd.next(max(1, n - 4), n);
            queries.push_back({type, type == 3 ? 0 : x});
        }
    }

    bool hasReport = false;
    for (const Query& query : queries) {
        hasReport = hasReport || query.type == 3;
    }
    if (!hasReport) {
        queries[rnd.next(static_cast<int>(queries.size()))] = {3, 0};
    }

    println(n, static_cast<int>(queries.size()));
    for (const Query& query : queries) {
        if (query.type == 3) {
            println(3);
        } else {
            println(query.type, query.x);
        }
    }

    return 0;
}
