#include "testlib.h"

#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

void addDebt(Matrix& d, int from, int to, int amount) {
    d[from][to] += amount;
    d[to][from] -= amount;
}

Matrix makeCase(int n, int mode) {
    Matrix d(n, vector<int>(n, 0));

    if (mode == 0) {
        return d;
    }

    if (mode == 1) {
        int limit = rnd.any(vector<int>{3, 10, 100, 1000000});
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int value = rnd.next(-limit, limit);
                d[i][j] = value;
                d[j][i] = -value;
            }
        }
        return d;
    }

    if (mode == 2) {
        int center = rnd.next(n);
        int sign = rnd.next(0, 1) == 0 ? -1 : 1;
        int base = rnd.any(vector<int>{1, 7, 1000, 1000000});
        for (int i = 0; i < n; ++i) {
            if (i == center) {
                continue;
            }
            int value = rnd.next(1, base) * sign;
            d[center][i] = value;
            d[i][center] = -value;
        }
        return d;
    }

    if (mode == 3) {
        int limit = rnd.any(vector<int>{5, 30, 1000000});
        for (int i = 0; i + 1 < n; ++i) {
            int value = rnd.next(1, limit);
            if (rnd.next(0, 1)) {
                value = -value;
            }
            d[i][i + 1] = value;
            d[i + 1][i] = -value;
        }
        return d;
    }

    if (mode == 4) {
        int amount = rnd.any(vector<int>{1, 2, 999999, 1000000});
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            addDebt(d, i, j, amount);
        }
        return d;
    }

    int limit = rnd.any(vector<int>{20, 1000, 500000});
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (rnd.next(0, 99) < 35) {
                int value = rnd.next(-limit, limit);
                d[i][j] = value;
                d[j][i] = -value;
            }
        }
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());
    for (int i = 0; i + 1 < n; ++i) {
        int value = rnd.next(1, limit);
        addDebt(d, order[i], order[i + 1], value);
    }

    return d;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 8);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int n;
        if (tc == 0 && rnd.next(0, 4) == 0) {
            n = 1;
        } else if (rnd.next(0, 4) == 0) {
            n = rnd.next(12, 20);
        } else {
            n = rnd.next(2, 8);
        }

        int mode = n == 1 ? 0 : rnd.next(0, 5);
        Matrix d = makeCase(n, mode);

        println(n);
        for (int i = 0; i < n; ++i) {
            println(d[i]);
        }
    }

    return 0;
}
