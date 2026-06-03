#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    int q = rnd.next(5, 32);

    vector<vector<int>> sets(n + 1);
    int nextValue = rnd.next(1, 50);

    auto addValue = [&](int index, int value) {
        if (find(sets[index].begin(), sets[index].end(), value) == sets[index].end()) {
            sets[index].push_back(value);
        }
    };

    if (mode == 0) {
        vector<int> pool;
        int poolSize = rnd.next(2, 8);
        for (int i = 0; i < poolSize; ++i) {
            pool.push_back(nextValue + i);
        }
        for (int i = 1; i <= n; ++i) {
            int size = rnd.next(0, min(5, poolSize));
            shuffle(pool.begin(), pool.end());
            for (int j = 0; j < size; ++j) {
                addValue(i, pool[j]);
            }
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            int size = (i % 3 == 0) ? 0 : rnd.next(1, 4);
            for (int j = 0; j < size; ++j) {
                addValue(i, nextValue++);
            }
        }
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i == center || rnd.next(0, 3) == 0) {
                addValue(i, 1000000000 - rnd.next(0, 20));
            }
            if (rnd.next(0, 1) == 0) {
                addValue(i, nextValue++);
            }
        }
    } else if (mode == 3) {
        int filled = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            int size = (i <= filled) ? rnd.next(1, 3) : 0;
            for (int j = 0; j < size; ++j) {
                addValue(i, i * 100 + j + rnd.next(0, 2));
            }
        }
        shuffle(sets.begin() + 1, sets.end());
    } else {
        for (int i = 1; i <= n; ++i) {
            int size = rnd.next(0, 6);
            int base = rnd.next(1, 1000);
            for (int j = 0; j < size; ++j) {
                addValue(i, base + j * rnd.next(1, 4));
            }
        }
    }

    bool hasElement = false;
    for (int i = 1; i <= n; ++i) {
        if (!sets[i].empty()) {
            hasElement = true;
        }
        shuffle(sets[i].begin(), sets[i].end());
    }
    if (!hasElement) {
        addValue(rnd.next(1, n), nextValue);
    }

    vector<vector<int>> commands;
    commands.push_back({2, rnd.next(1, n)});

    for (int i = 1; i < q; ++i) {
        bool makeQuery = rnd.next(0, 99) < (mode == 0 ? 45 : 30);
        if (makeQuery) {
            commands.push_back({2, rnd.next(1, n)});
        } else {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) {
                ++b;
            }
            commands.push_back({1, a, b});
        }
    }

    shuffle(commands.begin(), commands.end());

    println(n, q);
    for (int i = 1; i <= n; ++i) {
        cout << sets[i].size();
        for (int value : sets[i]) {
            cout << ' ' << value;
        }
        cout << '\n';
    }
    for (const auto& command : commands) {
        if (command[0] == 1) {
            println(command[0], command[1], command[2]);
        } else {
            println(command[0], command[1]);
        }
    }

    return 0;
}
