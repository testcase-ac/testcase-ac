#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIM = 1000000000000000000LL;

struct Query {
    long long a;
    long long b;
    int m;
    int n;
};

long long boundedMul(long long x, int m) {
    if (x > LIM / m) return LIM;
    return x * m;
}

vector<long long> powersForBase(int m) {
    vector<long long> powers{1};
    while (powers.back() <= LIM / m) powers.push_back(powers.back() * m);
    return powers;
}

long long randomValue(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

Query makeSmallRange() {
    int m = rnd.next(2, 10);
    long long a = randomValue(1, 200);
    long long b = min(LIM, a + randomValue(0, 300));
    int n = rnd.next(1, 12);
    return {a, b, m, n};
}

Query makeSingleton() {
    int m = rnd.next(2, 10);
    long long x;
    if (rnd.next(3) == 0) {
        x = rnd.next(1, 1000);
    } else {
        x = randomValue(1, LIM);
    }
    int n = rnd.next(1, 100);
    return {x, x, m, n};
}

Query makePowerWindow() {
    int m = rnd.next(2, 10);
    vector<long long> powers = powersForBase(m);
    long long center = rnd.any(powers);
    long long span = randomValue(0, min(10000LL, center - 1));
    long long a = max(1LL, center - span);
    long long b = min(LIM, center + span);
    int n = rnd.next(1, min(100, (int)powers.size() + 5));
    return {a, b, m, n};
}

Query makeWideRange() {
    int m = rnd.next(2, 10);
    long long a = randomValue(1, LIM / 2);
    long long width = randomValue(1000, LIM / 2);
    long long b = min(LIM, a + width);
    int n = rnd.next(1, 100);
    return {a, b, m, n};
}

Query makeDigitPatternRange() {
    int m = rnd.next(2, 10);
    vector<long long> powers = powersForBase(m);
    int len = rnd.next(1, (int)powers.size());
    long long base = powers[len - 1];
    long long next = boundedMul(base, m);
    long long a = base;
    long long b = min(LIM, next - 1);
    if (a > b) b = a;
    int n = rnd.next(1, min(100, len + 3));
    return {a, b, m, n};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(12, 35);
    vector<Query> queries;
    queries.reserve(T);

    queries.push_back({1, 1, 2, 1});
    queries.push_back({LIM, LIM, 10, 100});
    queries.push_back({LIM - 1, LIM, 2, 100});

    while ((int)queries.size() < T) {
        int mode = rnd.next(5);
        if (mode == 0) {
            queries.push_back(makeSmallRange());
        } else if (mode == 1) {
            queries.push_back(makeSingleton());
        } else if (mode == 2) {
            queries.push_back(makePowerWindow());
        } else if (mode == 3) {
            queries.push_back(makeWideRange());
        } else {
            queries.push_back(makeDigitPatternRange());
        }
    }

    shuffle(queries.begin(), queries.end());

    println((int)queries.size());
    for (const Query& q : queries) {
        println(q.a, q.b, q.m, q.n);
    }

    return 0;
}
