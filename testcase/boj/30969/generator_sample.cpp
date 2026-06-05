#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string makeDestination(int index, int mode) {
    string s;
    int x = index;
    do {
        s.push_back(static_cast<char>('a' + (x % 26)));
        x /= 26;
    } while (x > 0);

    if (mode == 0) {
        return s;
    }
    if (mode == 1) {
        reverse(s.begin(), s.end());
        return s + char('a' + (index % 26));
    }

    while (static_cast<int>(s.size()) < 15) {
        s.push_back(static_cast<char>('a' + ((index + static_cast<int>(s.size())) % 26)));
    }
    return s;
}

long long randomCost(long long jinjuCost, int mode) {
    if (mode == 0) {
        return rnd.next(1LL, 1000LL);
    }
    if (mode == 1) {
        long long lo = max(1LL, jinjuCost - 3);
        long long hi = min(1000LL, jinjuCost + 3);
        return rnd.next(lo, hi);
    }
    if (mode == 2) {
        return rnd.next(1001LL, 5000LL);
    }
    return rnd.next(999999999999000LL, 1000000000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(0, 4);
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 6);
    } else if (sizeMode == 2) {
        n = rnd.next(7, 15);
    } else {
        n = rnd.next(16, 40);
    }

    long long jinjuCost = rnd.next(1LL, 1000LL);
    int jinjuPos = rnd.next(0, n - 1);
    int nameMode = rnd.next(0, 2);

    vector<pair<string, long long>> rows;
    rows.reserve(n);
    set<string> used;
    used.insert("jinju");

    int destinationIndex = rnd.next(0, 1000);
    for (int i = 0; i < n; ++i) {
        if (i == jinjuPos) {
            rows.push_back({"jinju", jinjuCost});
            continue;
        }

        string d;
        do {
            d = makeDestination(destinationIndex++, nameMode);
        } while (d == "jinju" || used.count(d));
        used.insert(d);

        int costMode = rnd.next(0, 3);
        rows.push_back({d, randomCost(jinjuCost, costMode)});
    }

    println(n);
    for (const auto& row : rows) {
        println(row.first, row.second);
    }

    return 0;
}
