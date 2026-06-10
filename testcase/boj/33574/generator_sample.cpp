#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

using Query = vector<long long>;

long long randomValue(int mode) {
    if (mode == 0) return rnd.next(-10, 10);
    if (mode == 1) return rnd.any(vector<long long>{-1000000000LL, -1, 0, 1, 1000000000LL});
    if (mode == 2) return rnd.next(-1000000000, 1000000000);
    return rnd.next(-1000, 1000);
}

void addSort(vector<Query>& queries, int direction) {
    queries.push_back({1, direction});
}

void addInsert(vector<Query>& queries, int& size, int position, long long value) {
    queries.push_back({2, position, value});
    ++size;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int q = 0;
    int size = 0;
    vector<Query> queries;

    if (mode == 0) {
        q = rnd.next(1, 25);
        for (int i = 0; i < q; ++i) {
            addSort(queries, rnd.next(1, 2));
        }
    } else if (mode == 1) {
        q = rnd.next(8, 80);
        for (int i = 0; i < q; ++i) {
            int pos = rnd.any(vector<int>{0, size});
            addInsert(queries, size, pos, randomValue(i % 3));
        }
    } else if (mode == 2) {
        q = rnd.next(15, 120);
        for (int i = 0; i < q; ++i) {
            if (size > 0 && i % rnd.next(3, 6) == 0) {
                addSort(queries, (i / 3) % 2 + 1);
            } else {
                int pos = size == 0 ? 0 : rnd.next(0, size);
                addInsert(queries, size, pos, randomValue(rnd.next(0, 2)));
            }
        }
    } else if (mode == 3) {
        q = rnd.next(20, 150);
        for (int i = 0; i < q; ++i) {
            if (size > 0 && rnd.next(0, 99) < 35) {
                addSort(queries, rnd.next(1, 2));
            } else {
                int bucket = rnd.next(0, 3);
                int pos = 0;
                if (bucket == 0) pos = 0;
                else if (bucket == 1) pos = size;
                else pos = rnd.next(0, size);
                addInsert(queries, size, pos, randomValue(bucket));
            }
        }
    } else if (mode == 4) {
        q = rnd.next(30, 220);
        for (int i = 0; i < q; ++i) {
            if (size > 0 && rnd.next(0, 99) < 20) {
                addSort(queries, rnd.next(1, 2));
            } else {
                int bias = rnd.next(0, 4);
                int pos = 0;
                if (bias == 0) pos = 0;
                else if (bias == 1) pos = size;
                else if (bias == 2) pos = size / 2;
                else pos = rnd.next(0, size);
                addInsert(queries, size, pos, randomValue(rnd.next(0, 3)));
            }
        }
    } else {
        q = rnd.next(1, 3000);
        for (int i = 0; i < q; ++i) {
            if (size > 0 && rnd.next(0, 99) < 10) {
                addSort(queries, rnd.next(1, 2));
            } else {
                int pos = size == 0 ? 0 : rnd.next(0, size);
                addInsert(queries, size, pos, randomValue(rnd.next(0, 3)));
            }
        }
    }

    cout << queries.size() << '\n';
    for (const Query& query : queries) {
        for (int i = 0; i < (int)query.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << query[i];
        }
        cout << '\n';
    }

    return 0;
}
