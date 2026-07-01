#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

struct TestCase {
    int n;
    vector<int> cards;
};

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) return false;
    }
    return true;
}

vector<int> primesUpTo(int n) {
    vector<int> primes;
    for (int x = 2; x <= n; ++x) {
        if (isPrime(x)) primes.push_back(x);
    }
    return primes;
}

void addRepeated(vector<int>& cards, int value, int count) {
    for (int i = 0; i < count; ++i) cards.push_back(value);
}

TestCase makeCase(int n, int mode) {
    vector<int> cards;

    if (mode == 0) {
        addRepeated(cards, 1, rnd.next(1, 8));
    } else if (mode == 1) {
        int oneCount = rnd.next(1, 5);
        int other = rnd.next(1, n);
        addRepeated(cards, 1, oneCount);
        addRepeated(cards, other, rnd.next(1, 5));
    } else if (mode == 2 && n >= 2) {
        int base = rnd.next(2, max(2, n));
        int repeat = rnd.next(3, 12);
        addRepeated(cards, base, repeat);
        for (int x = base * 2; x <= n && (int)cards.size() < repeat + 5; x += base) {
            cards.push_back(x);
        }
    } else if (mode == 2) {
        addRepeated(cards, 1, rnd.next(1, 8));
    } else if (mode == 3) {
        vector<int> primes = primesUpTo(n);
        if (primes.empty()) {
            cards.push_back(1);
        } else {
            shuffle(primes.begin(), primes.end());
            int count = rnd.next(1, min<int>(8, primes.size()));
            for (int i = 0; i < count; ++i) {
                addRepeated(cards, primes[i], rnd.next(1, 3));
            }
            if (rnd.next(2) == 0) cards.push_back(1);
        }
    } else {
        int m = rnd.next(1, min(35, max(1, n * 2)));
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < m; ++i) {
            cards.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(cards.begin(), cards.end());
    return {n, cards};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    vector<TestCase> tests;
    int remainingN = 150;

    for (int tc = 0; tc < t; ++tc) {
        int remainingTests = t - tc;
        int maxN = remainingN - (remainingTests - 1);
        int n;

        if (tc == 0 && rnd.next(4) == 0) {
            n = 1;
        } else if (tc == 0 && rnd.next(4) == 0) {
            n = min(150, maxN);
        } else {
            n = rnd.next(1, min(40, maxN));
        }

        int mode = rnd.next(0, 4);
        tests.push_back(makeCase(n, mode));
        remainingN -= n;
    }

    println((int)tests.size());
    for (const TestCase& test : tests) {
        println(test.n, (int)test.cards.size());
        println(test.cards);
    }

    return 0;
}
