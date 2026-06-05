#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int signedValue(int x) {
    if (x == 0) return 0;
    return rnd.next(0, 1) ? x : -x;
}

int smallFactorProduct(int limit) {
    static const vector<int> primes = {2, 3, 5, 7, 11, 13};
    int value = 1;
    int steps = rnd.next(1, 4);
    for (int i = 0; i < steps; ++i) {
        int p = rnd.any(primes);
        if (value * p > limit) break;
        value *= p;
    }
    return signedValue(value);
}

int nonZeroValue(int limit = 100000) {
    int mode = rnd.next(0, 9);
    if (mode <= 4) return smallFactorProduct(limit);
    if (mode <= 6) return signedValue(rnd.next(1, min(limit, 30)));
    if (mode == 7) return signedValue(1);
    return signedValue(rnd.next(max(1, limit - 200), limit));
}

void addTerm(vector<int>& values, vector<char>& ops, char op, int value) {
    ops.push_back(op);
    values.push_back(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> values;
    vector<char> ops;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        values.push_back(rnd.next(0, 1) ? 0 : nonZeroValue());
        for (int i = 2; i <= n; ++i) {
            char op = rnd.next(0, 3) == 0 ? '/' : '*';
            int value = (op == '*') ? (rnd.next(0, 4) == 0 ? 0 : nonZeroValue()) : nonZeroValue();
            addTerm(values, ops, op, value);
        }
    } else if (mode == 1) {
        int pairs = rnd.next(1, 6);
        values.push_back(nonZeroValue(2000));
        vector<pair<char, int>> terms;
        for (int i = 0; i < pairs; ++i) {
            int value = nonZeroValue(1000);
            terms.push_back({'*', value});
            terms.push_back({'/', rnd.next(0, 1) ? value : -value});
        }
        shuffle(terms.begin(), terms.end());
        int keep = rnd.next(1, static_cast<int>(terms.size()));
        for (int i = 0; i < keep; ++i) addTerm(values, ops, terms[i].first, terms[i].second);
    } else if (mode == 2) {
        int n = rnd.next(2, 14);
        values.push_back(rnd.next(0, 1) ? 1 : nonZeroValue(500));
        for (int i = 2; i <= n; ++i) {
            char op = rnd.next(0, 2) == 0 ? '/' : '*';
            int value = op == '/' ? rnd.any(vector<int>{17, 19, 23, 29, 31, 37}) : nonZeroValue(200);
            addTerm(values, ops, op, signedValue(value));
        }
    } else if (mode == 3) {
        int n = rnd.next(1, 10);
        values.push_back(rnd.any(vector<int>{-100000, -99991, -1, 1, 99991, 100000}));
        for (int i = 2; i <= n; ++i) {
            char op = rnd.next(0, 1) ? '*' : '/';
            int value = rnd.any(vector<int>{-100000, -99991, -2, -1, 1, 2, 99991, 100000});
            addTerm(values, ops, op, value);
        }
    } else if (mode == 4) {
        int n = rnd.next(1, 18);
        values.push_back(rnd.next(0, 1) ? 1 : -1);
        for (int i = 2; i <= n; ++i) {
            char op = rnd.next(0, 1) ? '*' : '/';
            int value = rnd.next(0, 5) == 0 && op == '*' ? 0 : (rnd.next(0, 1) ? 1 : -1);
            addTerm(values, ops, op, value);
        }
    } else {
        int n = rnd.next(8, 24);
        values.push_back(nonZeroValue(100));
        for (int i = 2; i <= n; ++i) {
            char op = rnd.next(0, 99) < 55 ? '*' : '/';
            int value = nonZeroValue(300);
            addTerm(values, ops, op, value);
        }
    }

    println(static_cast<int>(values.size()));
    cout << values[0];
    for (int i = 1; i < static_cast<int>(values.size()); ++i) {
        cout << ' ' << ops[i - 1] << ' ' << values[i];
    }
    cout << '\n';

    return 0;
}
