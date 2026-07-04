#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readSpace();
    int d = inf.readInt(1, 10, "d");
    inf.readSpace();
    int cash = inf.readInt(1, 100000, "x");
    inf.readEoln();

    vector<vector<int>> price(d, vector<int>(n));
    for (int i = 0; i < d; ++i) {
        price[i] = inf.readInts(n, 1, 100000, "p_i_j");
        inf.readEoln();
    }
    inf.readEof();

    for (int day = 1; day < d; ++day) {
        vector<int> profit(cash + 1, 0);
        for (int stock = 0; stock < n; ++stock) {
            int cost = price[day - 1][stock];
            int gain = price[day][stock] - cost;
            if (gain <= 0) {
                continue;
            }
            for (int money = cost; money <= cash; ++money) {
                profit[money] = max(profit[money], profit[money - cost] + gain);
            }
        }

        cash += profit[cash];
        ensuref(cash <= 100000,
                "optimal final cash guarantee exceeded by end of day %d: %d",
                day + 1, cash);
    }
}
