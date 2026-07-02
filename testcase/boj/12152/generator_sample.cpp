#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct CaseData {
    int c;
    long long v;
    vector<long long> coins;
};

vector<long long> sortedCoins(set<long long> values) {
    vector<long long> coins(values.begin(), values.end());
    return coins;
}

CaseData smallCoverageCase() {
    int c = rnd.next(1, 5);
    long long v = rnd.next(1LL, 80LL);
    set<long long> values;

    long long covered = 0;
    while (covered < v && static_cast<int>(values.size()) < rnd.next(1, 8)) {
        long long next = rnd.next(covered + 1, min(v, covered + c + 2LL));
        values.insert(next);
        covered += next * c;
    }
    if (values.empty()) values.insert(rnd.next(1LL, v));

    return {c, v, sortedCoins(values)};
}

CaseData missingOneCase() {
    int c = rnd.next(1, 100);
    long long v = rnd.next(3LL, 200LL);
    int d = rnd.next(1, static_cast<int>(min(8LL, v - 1)));
    set<long long> values;

    while (static_cast<int>(values.size()) < d) {
        values.insert(rnd.next(2LL, v));
    }

    return {c, v, sortedCoins(values)};
}

CaseData densePrefixCase() {
    int c = rnd.next(1, 100);
    int d = rnd.next(4, 20);
    long long v = rnd.next(static_cast<long long>(d), 300LL);
    set<long long> values;

    for (int x = 1; x <= d; ++x) values.insert(x);

    return {c, v, sortedCoins(values)};
}

CaseData largeValueCase() {
    int c = rnd.next(1, 100);
    long long v = rnd.next(100000000LL, 1000000000LL);
    int d = rnd.next(2, 12);
    set<long long> values;

    values.insert(1);
    long long current = 1;
    while (static_cast<int>(values.size()) < d) {
        current += rnd.next(1LL, max(2LL, current * rnd.next(1, 4)));
        if (current > v) break;
        values.insert(current);
    }
    while (static_cast<int>(values.size()) < d) {
        values.insert(rnd.next(1LL, v));
    }

    return {c, v, sortedCoins(values)};
}

CaseData maxDenominationCountCase() {
    int c = rnd.next(1, 100);
    long long v = rnd.next(100LL, 500LL);
    set<long long> values;

    for (int x = 1; x <= 100; ++x) values.insert(x);

    return {c, v, sortedCoins(values)};
}

CaseData randomCase() {
    int c = rnd.next(1, 100);
    long long v = rnd.next(1LL, 1000LL);
    int d = rnd.next(1, static_cast<int>(min(20LL, v)));
    set<long long> values;

    while (static_cast<int>(values.size()) < d) {
        values.insert(rnd.next(1LL, v));
    }

    return {c, v, sortedCoins(values)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 18);
    vector<CaseData> cases;
    cases.push_back(smallCoverageCase());
    cases.push_back(missingOneCase());
    cases.push_back(densePrefixCase());
    cases.push_back(largeValueCase());
    cases.push_back(maxDenominationCountCase());

    while (static_cast<int>(cases.size()) < t) {
        int mode = rnd.next(0, 5);
        if (mode == 0) {
            cases.push_back(smallCoverageCase());
        } else if (mode == 1) {
            cases.push_back(missingOneCase());
        } else if (mode == 2) {
            cases.push_back(densePrefixCase());
        } else if (mode == 3) {
            cases.push_back(largeValueCase());
        } else if (mode == 4) {
            cases.push_back(maxDenominationCountCase());
        } else {
            cases.push_back(randomCase());
        }
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (const CaseData& test : cases) {
        println(test.c, static_cast<int>(test.coins.size()), test.v);
        println(test.coins);
    }

    return 0;
}
