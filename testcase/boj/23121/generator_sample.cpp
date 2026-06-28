#include "testlib.h"

#include <vector>

using namespace std;

struct Query {
    int a;
    int b;
    int c;
    int d;
};

int modAdd(int x, int y, int p) {
    return (int)(((long long)x + y) % p);
}

int randValue(int p) {
    if (rnd.next(0, 4) == 0) {
        vector<int> edgeValues = {0, 1 % p, (p - 1) % p};
        return rnd.any(edgeValues);
    }
    return rnd.next(0, p - 1);
}

pair<int, int> randStartPair(int p) {
    while (true) {
        int a = randValue(p);
        int b = randValue(p);
        if (modAdd(a, b, p) != 0) {
            return {a, b};
        }
    }
}

pair<int, int> pairWithSum(int p, int sum) {
    int x = randValue(p);
    int y = (sum - x + p) % p;
    return {x, y};
}

pair<int, int> applyOperation(pair<int, int> value, int p, int op) {
    int a = value.first;
    int b = value.second;
    if (op == 0) {
        return {(int)(2LL * a % p), (b + p - a) % p};
    }
    return {(a + p - b) % p, (int)(2LL * b % p)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 17, 31, 97, 1000000007};
    int p = rnd.any(primes);
    int q = rnd.next(8, 24);

    vector<Query> queries;
    for (int i = 0; i < q; ++i) {
        auto start = randStartPair(p);
        int startSum = modAdd(start.first, start.second, p);
        int mode = rnd.next(0, 5);
        pair<int, int> target;

        if (mode == 0) {
            target = start;
        } else if (mode == 1) {
            target = start;
            int steps = rnd.next(1, 8);
            for (int step = 0; step < steps; ++step) {
                target = applyOperation(target, p, rnd.next(0, 1));
            }
        } else if (mode == 2) {
            target = pairWithSum(p, startSum);
        } else if (mode == 3) {
            int otherSum = rnd.next(0, p - 1);
            if (otherSum == startSum) {
                otherSum = (otherSum + 1) % p;
            }
            target = pairWithSum(p, otherSum);
        } else if (mode == 4) {
            target = {randValue(p), randValue(p)};
        } else {
            target = {0, rnd.next(0, p - 1)};
        }

        queries.push_back({start.first, start.second, target.first, target.second});
    }

    println(p, q);
    for (const Query& query : queries) {
        println(query.a, query.b, query.c, query.d);
    }

    return 0;
}
