#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

namespace {

void collectSolutions(const vector<long long>& prices,
                      int index,
                      vector<bool>& used,
                      vector<long long>& salePrices,
                      set<vector<long long>>& solutions) {
    while (index < static_cast<int>(prices.size()) && used[index]) {
        ++index;
    }
    if (index == static_cast<int>(prices.size())) {
        solutions.insert(salePrices);
        return;
    }

    long long sale = prices[index];
    used[index] = true;

    if (sale % 3 == 0) {
        long long regular = sale / 3 * 4;
        for (int j = index + 1; j < static_cast<int>(prices.size()); ++j) {
            if (!used[j] && prices[j] == regular) {
                used[j] = true;
                salePrices.push_back(sale);
                collectSolutions(prices, index + 1, used, salePrices, solutions);
                salePrices.pop_back();
                used[j] = false;
                if (solutions.size() > 1) {
                    break;
                }
            }
        }
    }

    used[index] = false;
}

bool hasUniqueSolution(const vector<long long>& prices) {
    vector<bool> used(prices.size(), false);
    vector<long long> salePrices;
    set<vector<long long>> solutions;
    collectSolutions(prices, 0, used, salePrices, solutions);
    return solutions.size() == 1;
}

vector<long long> buildCase(int n, int mode) {
    vector<long long> salePrices;

    if (mode == 0) {
        int start = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            salePrices.push_back(3LL * (start + i));
        }
    } else if (mode == 1) {
        long long sale = 3LL * rnd.next(1, 40);
        salePrices.assign(n, sale);
    } else if (mode == 2) {
        long long base = 3LL * rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            salePrices.push_back(base);
            if (rnd.next(0, 1) == 1) {
                base += 3LL * rnd.next(1, 3);
            }
        }
    } else if (mode == 3) {
        long long sale = 3LL * rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            salePrices.push_back(sale);
            sale = sale / 3 * 4;
            if (sale % 3 != 0) {
                sale = 3LL * ((sale + 2) / 3);
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            salePrices.push_back(3LL * rnd.next(1, 250000000));
        }
    }

    sort(salePrices.begin(), salePrices.end());

    vector<long long> prices;
    for (long long sale : salePrices) {
        prices.push_back(sale);
        prices.push_back(sale / 3 * 4);
    }
    sort(prices.begin(), prices.end());
    return prices;
}

vector<long long> randomValidCase() {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int n = rnd.next(1, 4);
        int mode = rnd.next(0, 4);
        vector<long long> prices = buildCase(n, mode);
        if (prices.back() <= 1000000000LL && hasUniqueSolution(prices)) {
            return prices;
        }
    }

    int sale = 3 * rnd.next(1, 100);
    return {sale, sale / 3 * 4};
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        vector<long long> prices = randomValidCase();
        println(static_cast<int>(prices.size() / 2));
        println(prices);
    }

    return 0;
}
