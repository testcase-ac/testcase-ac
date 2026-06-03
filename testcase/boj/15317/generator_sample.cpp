#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000LL;

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 20);
    int m = rnd.next(1, 20);
    long long x = rnd.next(0LL, 100LL);
    vector<long long> costs(n), budgets(m);

    auto fillSmall = [&]() {
        int high = rnd.next(0, 40);
        for (long long& c : costs) c = rnd.next(0, high);
        for (long long& s : budgets) s = rnd.next(0, high);
        x = rnd.next(0LL, 1LL * high * min(n, m));
    };

    if (mode == 0) {
        fillSmall();
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
        costs.assign(n, 0);
        budgets.assign(m, 0);
        x = rnd.next(0LL, 3LL);
        int expensive = rnd.next(0, n - 1);
        costs[expensive] = rnd.next(0LL, 5LL);
    } else if (mode == 2) {
        n = rnd.next(6, 24);
        m = rnd.next(6, 24);
        costs.resize(n);
        budgets.resize(m);
        long long base = rnd.next(5LL, 50LL);
        for (long long& c : costs) c = max(0LL, base + rnd.next(-5LL, 8LL));
        for (long long& s : budgets) s = max(0LL, base + rnd.next(-8LL, 5LL));
        x = rnd.next(0LL, 20LL);
    } else if (mode == 3) {
        n = rnd.next(1, 30);
        m = rnd.next(1, 30);
        costs.resize(n);
        budgets.resize(m);
        long long value = rnd.next(0LL, 25LL);
        for (long long& c : costs) c = value;
        for (long long& s : budgets) s = value + rnd.next(-value, 10LL);
        x = rnd.next(0LL, 30LL);
    } else if (mode == 4) {
        n = rnd.next(8, 35);
        m = rnd.next(8, 35);
        costs.resize(n);
        budgets.resize(m);
        for (int i = 0; i < n; ++i) costs[i] = i * rnd.next(1LL, 4LL) + rnd.next(0LL, 3LL);
        for (int i = 0; i < m; ++i) budgets[i] = i * rnd.next(1LL, 4LL) + rnd.next(0LL, 3LL);
        x = rnd.next(0LL, 80LL);
    } else if (mode == 5) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
        costs.resize(n);
        budgets.resize(m);
        for (long long& c : costs) c = rnd.next(0, 1) ? LIMIT : rnd.next(LIMIT - 20, LIMIT);
        for (long long& s : budgets) s = rnd.next(0, 1) ? LIMIT : rnd.next(0LL, 20LL);
        x = rnd.next(0, 1) ? LIMIT : rnd.next(0LL, 50LL);
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        costs.resize(n);
        budgets.resize(m);
        long long cBase = rnd.next(0LL, 100LL);
        long long sBase = rnd.next(0LL, 100LL);
        for (int i = 0; i < n; ++i) costs[i] = min(LIMIT, cBase + i * rnd.next(0LL, 7LL));
        for (int i = 0; i < m; ++i) budgets[i] = min(LIMIT, sBase + (m - 1 - i) * rnd.next(0LL, 7LL));
        x = rnd.next(0LL, 120LL);
    }

    shuffle(costs.begin(), costs.end());
    shuffle(budgets.begin(), budgets.end());

    println(n, m, x);
    println(costs);
    println(budgets);

    return 0;
}
