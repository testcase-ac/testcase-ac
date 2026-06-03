#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int boundedAdd(int value, int delta) {
    return min(1000000000, value + delta);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 12);
    if (mode == 1 || mode == 3 || mode == 5) m = rnd.next(n, max(n, 12));
    if (mode == 2) m = rnd.next(1, max(1, n - 1));

    vector<pair<int, int>> cows;
    vector<pair<int, int>> grass;

    int basePrice = (mode == 5 ? rnd.next(999999930, 999999990) : rnd.next(1, 40));
    int baseGreen = (mode == 5 ? rnd.next(999999930, 999999990) : rnd.next(1, 40));

    for (int i = 0; i < n; ++i) {
        int price = boundedAdd(basePrice, rnd.next(0, 20));
        int green = boundedAdd(baseGreen, rnd.next(0, 20));
        if (mode == 3) green = baseGreen;
        cows.push_back({price, green});
    }

    if (mode == 1 || mode == 3 || mode == 5) {
        for (int i = 0; i < n; ++i) {
            grass.push_back({boundedAdd(cows[i].first, rnd.next(0, 8)),
                             boundedAdd(cows[i].second, rnd.next(0, 8))});
        }
        while ((int)grass.size() < m) {
            int from = rnd.next(0, n - 1);
            grass.push_back({boundedAdd(cows[from].first, rnd.next(0, 15)),
                             boundedAdd(cows[from].second, rnd.next(0, 15))});
        }
    } else {
        for (int i = 0; i < m; ++i) {
            int from = rnd.next(0, n - 1);
            int price = cows[from].first;
            int green = cows[from].second;
            if (mode == 4 || rnd.next(0, 1) == 0)
                price = max(1, price - rnd.next(1, min(price, 10)));
            else
                green = max(1, green - rnd.next(1, min(green, 10)));
            grass.push_back({price, green});
        }
    }

    shuffle(cows.begin(), cows.end());
    shuffle(grass.begin(), grass.end());

    println(n, m);
    for (auto cow : cows) println(cow.first, cow.second);
    for (auto type : grass) println(type.first, type.second);

    return 0;
}
