#include "testlib.h"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <vector>

using namespace std;

namespace {
const long long kMaxValue = 1000000000000000000LL;

long long smallPrice() {
    return rnd.next(1, 60);
}

long long largePrice() {
    return kMaxValue - rnd.next(0, 1000);
}

long long wideBudget() {
    long long high = rnd.next(0, 1000000);
    long long low = rnd.next(0, 999999999);
    long long value = high * 1000000000000LL + low;
    return min(value, kMaxValue);
}

void printCase(const vector<long long>& prices, long long budget) {
    std::printf("%d\n", static_cast<int>(prices.size()));
    for (int i = 0; i < static_cast<int>(prices.size()); ++i) {
        if (i > 0) std::printf(" ");
        std::printf("%lld", prices[i]);
    }
    std::printf("\n");
    std::printf("%lld\n", budget);
}
}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 10);
    vector<long long> prices(n);
    long long budget = 0;

    if (mode == 0) {
        for (long long& price : prices) price = smallPrice();
        budget = rnd.next(0, static_cast<int>(*min_element(prices.begin(), prices.end()) - 1));
    } else if (mode == 1) {
        n = 1;
        prices.assign(1, rnd.next(1, 100));
        budget = rnd.next(0, 300);
    } else if (mode == 2) {
        int base = rnd.next(1, 20);
        for (long long& price : prices) price = rnd.next(max(1, base - 1), base + 1);
        budget = rnd.next(0, 200);
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        prices.assign(n, rnd.next(1, 5));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) prices[i] += rnd.next(0, 2);
        }
        budget = rnd.next(0, 500);
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        prices.assign(n, largePrice());
        prices[0] = rnd.next(1, 5);
        prices[rnd.next(1, n - 1)] = largePrice();
        budget = largePrice();
    } else if (mode == 5) {
        n = rnd.next(2, 10);
        prices.resize(n);
        for (long long& price : prices) price = smallPrice();
        prices[0] = rnd.next(1, 3);
        prices[rnd.next(1, n - 1)] = rnd.next(1, 12);
        budget = rnd.next(50, 1000000);
    } else if (mode == 6) {
        for (long long& price : prices) price = rnd.next(1, 10);
        budget = rnd.next(0, 1000000) * 1000000LL + rnd.next(0, 999999);
    } else {
        for (long long& price : prices) {
            price = rnd.next(0, 1) == 0 ? smallPrice() : largePrice();
        }
        budget = wideBudget();
    }

    for (int i = 0; i < static_cast<int>(prices.size()); ++i) {
        int j = rnd.next(i, static_cast<int>(prices.size()) - 1);
        swap(prices[i], prices[j]);
    }
    printCase(prices, budget);
    return 0;
}
