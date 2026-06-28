#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

long long randomDay(long long m) {
    if (m <= 1000000LL) return rnd.next(1LL, m);
    int band = rnd.next(0, 4);
    if (band == 0) return rnd.next(1LL, 20LL);
    if (band == 1) return m - rnd.next(0LL, 20LL);
    return rnd.next(1LL, m);
}

vector<long long> uniqueSortedDays(long long m, int k) {
    set<long long> chosen;
    chosen.insert(1);
    if (k >= 2) chosen.insert(m);
    while ((int)chosen.size() < k) chosen.insert(randomDay(m));

    vector<long long> days(chosen.begin(), chosen.end());
    shuffle(days.begin(), days.end());
    sort(days.begin(), days.end());
    return days;
}

long long randomCandy(long long n) {
    if (n == 1) return 1;
    int mode = rnd.next(0, 3);
    if (mode == 0) return 1;
    if (mode == 1) return n;
    return rnd.next(1LL, n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    long long n, m;
    int k;
    vector<pair<long long, long long>> fixedDays;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1LL, 30LL);
        k = rnd.next(1, (int)min(m, 8LL));
        vector<long long> days = uniqueSortedDays(m, k);
        for (long long day : days) fixedDays.push_back({day, 1});
    } else if (mode == 1) {
        n = rnd.next(2LL, 8LL);
        m = rnd.next(2LL, 20LL);
        k = rnd.next(1, (int)m);
        vector<long long> days = uniqueSortedDays(m, k);
        long long lastCandy = randomCandy(n);
        for (long long day : days) {
            if (rnd.next(0, 99) < 45) {
                fixedDays.push_back({day, lastCandy});
            } else {
                lastCandy = randomCandy(n);
                fixedDays.push_back({day, lastCandy});
            }
        }
    } else if (mode == 2) {
        n = rnd.next(2LL, 100LL);
        long long gap = rnd.next(1LL, 12LL);
        long long start = rnd.next(1LL, 5LL);
        m = start + gap + rnd.next(0LL, 5LL);
        k = 2;
        long long firstCandy = randomCandy(n);
        long long secondCandy = rnd.next(0, 1) ? firstCandy : randomCandy(n);
        fixedDays.push_back({start, firstCandy});
        fixedDays.push_back({start + gap, secondCandy});
    } else if (mode == 3) {
        n = rnd.any(vector<long long>{2LL, 3LL, 1000000000LL});
        m = rnd.next(1000000000000LL, 1000000000000000000LL);
        k = rnd.next(1, 8);
        vector<long long> days = uniqueSortedDays(m, k);
        for (long long day : days) fixedDays.push_back({day, randomCandy(n)});
    } else {
        n = rnd.next(2LL, 20LL);
        m = rnd.next(1LL, 80LL);
        k = rnd.next(1, (int)min(m, 20LL));
        vector<long long> days = uniqueSortedDays(m, k);
        for (long long day : days) fixedDays.push_back({day, randomCandy(n)});
    }

    println(n, m, k);
    for (auto [day, candy] : fixedDays) println(day, candy);

    return 0;
}
