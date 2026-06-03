#include "testlib.h"

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

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 4, "N");
        inf.readEoln();

        vector<long long> prices = inf.readLongs(2 * n, 1LL, 1000000000LL, "P_i");
        inf.readEoln();

        for (int i = 1; i < 2 * n; ++i) {
            ensuref(prices[i - 1] <= prices[i],
                    "prices must be non-decreasing: P_%d=%lld, P_%d=%lld",
                    i,
                    prices[i - 1],
                    i + 1,
                    prices[i]);
        }

        vector<bool> used(2 * n, false);
        vector<long long> salePrices;
        set<vector<long long>> solutions;
        collectSolutions(prices, 0, used, salePrices, solutions);
        ensuref(solutions.size() == 1,
                "test case must have exactly one sale-price solution");
    }

    inf.readEof();
}
