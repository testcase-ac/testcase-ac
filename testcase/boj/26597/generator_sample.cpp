#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const long long MIN_X = -1000000000000000000LL;
const long long MAX_X = 1000000000000000000LL;

long long randomValue() {
    int kind = rnd.next(0, 5);
    if (kind == 0) return rnd.next(-20LL, 20LL);
    if (kind == 1) return rnd.next(-1000000LL, 1000000LL);
    if (kind == 2) return rnd.next(MIN_X, MIN_X + 30);
    if (kind == 3) return rnd.next(MAX_X - 30, MAX_X);
    return rnd.next(MIN_X, MAX_X);
}

void addQuery(vector<pair<long long, char>>& queries, long long x, char direction) {
    queries.push_back({x, direction});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<long long, char>> queries;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int q = rnd.next(1, 12);
        for (int i = 0; i < q; ++i) {
            addQuery(queries, randomValue(), rnd.next(0, 1) ? '^' : 'v');
        }
    } else if (mode == 1) {
        long long favorite = rnd.next(-1000LL, 1000LL);
        int lowerCount = rnd.next(1, 5);
        int upperCount = rnd.next(1, 5);
        for (int i = 0; i < lowerCount; ++i) {
            addQuery(queries, rnd.next(max(MIN_X, favorite - 50), favorite - 1), '^');
        }
        for (int i = 0; i < upperCount; ++i) {
            addQuery(queries, rnd.next(favorite + 1, min(MAX_X, favorite + 50)), 'v');
        }
        shuffle(queries.begin(), queries.end());
    } else if (mode == 2) {
        long long answer = rnd.next(-1000LL, 1000LL);
        int noise = rnd.next(0, 4);
        for (int i = 0; i < noise; ++i) {
            if (rnd.next(0, 1)) {
                addQuery(queries, rnd.next(answer - 100, answer - 1), '^');
            } else {
                addQuery(queries, rnd.next(answer + 1, answer + 100), 'v');
            }
        }
        addQuery(queries, answer - 1, '^');
        addQuery(queries, answer + 1, 'v');
        if (rnd.next(0, 1)) shuffle(queries.begin(), queries.end());
    } else if (mode == 3) {
        long long pivot = rnd.next(-1000LL, 1000LL);
        int before = rnd.next(0, 4);
        for (int i = 0; i < before; ++i) {
            addQuery(queries, rnd.next(pivot - 100, pivot + 100), rnd.next(0, 1) ? '^' : 'v');
        }
        addQuery(queries, pivot, '^');
        addQuery(queries, pivot, 'v');
    } else if (mode == 4) {
        int repeats = rnd.next(1, 6);
        long long x = rnd.any(vector<long long>{MIN_X, MIN_X + 1, -1, 0, 1, MAX_X - 1, MAX_X});
        char direction = rnd.next(0, 1) ? '^' : 'v';
        for (int i = 0; i < repeats; ++i) addQuery(queries, x, direction);
    } else {
        addQuery(queries, MIN_X, '^');
        addQuery(queries, MAX_X, 'v');
        int extra = rnd.next(0, 5);
        for (int i = 0; i < extra; ++i) addQuery(queries, randomValue(), rnd.next(0, 1) ? '^' : 'v');
        if (rnd.next(0, 1)) shuffle(queries.begin(), queries.end());
    }

    println(static_cast<int>(queries.size()));
    for (auto [x, direction] : queries) {
        println(x, direction);
    }

    return 0;
}
