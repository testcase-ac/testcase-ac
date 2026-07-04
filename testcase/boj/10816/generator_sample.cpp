#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int MIN_VALUE = -10000000;
const int MAX_VALUE = 10000000;

int nearBoundaryValue() {
    if (rnd.next(0, 1) == 0) {
        return MIN_VALUE + rnd.next(0, 20);
    }
    return MAX_VALUE - rnd.next(0, 20);
}

int randomSmallValue() {
    return rnd.next(-30, 30);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    int m = rnd.next(1, 45);
    vector<int> cards;
    vector<int> queries;

    if (mode == 0) {
        vector<int> pool;
        int poolSize = rnd.next(1, 7);
        for (int i = 0; i < poolSize; ++i) {
            pool.push_back(randomSmallValue());
        }
        for (int i = 0; i < n; ++i) {
            cards.push_back(rnd.any(pool));
        }
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 2) == 0) {
                queries.push_back(rnd.any(pool));
            } else {
                queries.push_back(randomSmallValue());
            }
        }
    } else if (mode == 1) {
        int base = rnd.next(-1000, 1000);
        int step = rnd.next(1, 7);
        for (int i = 0; i < n; ++i) {
            cards.push_back(base + (i % 9) * step);
        }
        for (int i = 0; i < m; ++i) {
            int offset = rnd.next(-3, 12);
            queries.push_back(base + offset * step);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        m = rnd.next(2, 35);
        for (int i = 0; i < n; ++i) {
            cards.push_back(nearBoundaryValue());
        }
        cards.push_back(MIN_VALUE);
        cards.push_back(MAX_VALUE);
        n = (int)cards.size();
        for (int i = 0; i < m; ++i) {
            if (i % 4 == 0) {
                queries.push_back(MIN_VALUE);
            } else if (i % 4 == 1) {
                queries.push_back(MAX_VALUE);
            } else {
                queries.push_back(nearBoundaryValue());
            }
        }
    } else if (mode == 3) {
        n = rnd.next(20, 80);
        m = rnd.next(20, 80);
        int repeated = rnd.next(-5, 5);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) != 0) {
                cards.push_back(repeated);
            } else {
                cards.push_back(randomSmallValue());
            }
        }
        for (int i = 0; i < m; ++i) {
            queries.push_back(i % 3 == 0 ? repeated : randomSmallValue());
        }
    } else if (mode == 4) {
        n = rnd.next(5, 50);
        m = rnd.next(5, 50);
        for (int i = 0; i < n; ++i) {
            cards.push_back(rnd.next(-100000, 100000));
        }
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 1) == 0) {
                queries.push_back(rnd.any(cards));
            } else {
                queries.push_back(rnd.next(-100000, 100000));
            }
        }
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(35, 90);
        for (int i = 0; i < n; ++i) {
            cards.push_back(randomSmallValue());
        }
        for (int i = 0; i < m; ++i) {
            if (i % 5 == 0) {
                queries.push_back(rnd.any(cards));
            } else {
                queries.push_back(randomSmallValue());
            }
        }
    }

    shuffle(cards.begin(), cards.end());
    shuffle(queries.begin(), queries.end());

    println((int)cards.size());
    println(cards);
    println((int)queries.size());
    println(queries);

    return 0;
}
