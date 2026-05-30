#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read C, D, M
    int C = inf.readInt(1, 50, "C");
    inf.readSpace();
    int D = inf.readInt(2, 10, "D");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readEoln();

    vector<vector<int>> prices(C, vector<int>(D));

    // Read C lines, each with D integers in [1,1000]
    for (int i = 0; i < C; ++i) {
        prices[i] = inf.readInts(D, 1, 1000, "price");
        inf.readEoln();
    }

    long long money = M;
    for (int day = 0; day + 1 < D; ++day) {
        vector<long long> best(money + 1);
        for (long long cash = 0; cash <= money; ++cash) {
            best[cash] = cash;
        }
        for (int stock = 0; stock < C; ++stock) {
            int buy = prices[stock][day];
            int sell = prices[stock][day + 1];
            for (long long cash = buy; cash <= money; ++cash) {
                best[cash] = max(best[cash], best[cash - buy] + sell);
            }
        }
        money = best[money];
        ensuref(money <= 500000,
                "maximum final money guarantee exceeded after day %d: %lld",
                day + 2, money);
    }

    inf.readEof();
}
