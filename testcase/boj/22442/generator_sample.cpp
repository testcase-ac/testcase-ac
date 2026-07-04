#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int simulateFinalCash(const vector<vector<int>>& price, int cash) {
    int d = int(price.size());
    int n = int(price[0].size());

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
        if (cash > 100000) {
            return cash;
        }
    }

    return cash;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 10);
    int d = rnd.next(1, 10);
    int cash = rnd.next(1, 200);
    int mode = rnd.next(0, 5);

    vector<vector<int>> price(d, vector<int>(n));
    bool valid = false;
    for (int attempt = 0; attempt < 200; ++attempt) {
        if (mode == 0) {
            cash = rnd.next(1, 20);
            for (int stock = 0; stock < n; ++stock) {
                int base = rnd.next(1, 20);
                for (int day = 0; day < d; ++day) {
                    price[day][stock] = base;
                }
            }
        } else if (mode == 1) {
            cash = rnd.next(1, 80);
            for (int stock = 0; stock < n; ++stock) {
                int current = rnd.next(1, 40);
                for (int day = 0; day < d; ++day) {
                    current = max(1, current + rnd.next(-8, 12));
                    price[day][stock] = current;
                }
            }
        } else if (mode == 2) {
            cash = rnd.next(30, 250);
            for (int stock = 0; stock < n; ++stock) {
                int low = rnd.next(1, 30);
                int high = low + rnd.next(1, 70);
                for (int day = 0; day < d; ++day) {
                    price[day][stock] = (day % 2 == stock % 2) ? low : high;
                }
            }
        } else if (mode == 3) {
            cash = rnd.next(1, 1000);
            for (int day = 0; day < d; ++day) {
                for (int stock = 0; stock < n; ++stock) {
                    price[day][stock] = rnd.next(90000, 100000);
                }
            }
        } else if (mode == 4) {
            cash = rnd.next(90000, 99999);
            for (int day = 0; day < d; ++day) {
                for (int stock = 0; stock < n; ++stock) {
                    price[day][stock] = rnd.next(cash + 1, 100000);
                }
            }
        } else {
            cash = rnd.next(1, 300);
            for (int day = 0; day < d; ++day) {
                int band = rnd.next(1, 80);
                for (int stock = 0; stock < n; ++stock) {
                    price[day][stock] = rnd.next(1, band + stock * 7 + 30);
                }
            }
        }

        if (simulateFinalCash(price, cash) <= 100000) {
            valid = true;
            break;
        }
    }

    if (!valid) {
        cash = rnd.next(1, 100);
        for (int stock = 0; stock < n; ++stock) {
            int base = rnd.next(1, 100);
            for (int day = 0; day < d; ++day) {
                price[day][stock] = base;
            }
        }
    }

    println(n, d, cash);
    for (const vector<int>& row : price) {
        println(row);
    }

    return 0;
}
