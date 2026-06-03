#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomArray(int n, int lo, int hi) {
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = rnd.next(lo, hi);
    }
    return values;
}

void applyTransfers(vector<int>& values, int steps, int maxAmount) {
    int n = (int)values.size();
    for (int step = 0; step < steps; ++step) {
        vector<int> donors, receivers;
        for (int i = 0; i < n; ++i) {
            if (values[i] > 1) donors.push_back(i);
            if (values[i] < 100) receivers.push_back(i);
        }
        if (donors.empty() || receivers.empty()) return;

        int from = rnd.any(donors);
        int to = rnd.any(receivers);
        for (int attempt = 0; attempt < 10 && from == to && receivers.size() > 1; ++attempt) {
            to = rnd.any(receivers);
        }
        if (from == to) continue;

        int amount = rnd.next(1, min({maxAmount, values[from] - 1, 100 - values[to]}));
        values[from] -= amount;
        values[to] += amount;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a, b;

    if (mode == 0) {
        n = rnd.next(2, 12);
        a = randomArray(n, 1, 100);
        b = a;
    } else if (mode == 1) {
        n = 2;
        a = {rnd.next(50, 100), rnd.next(1, 50)};
        b = {a[1], a[0]};
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        a = randomArray(n, 35, 65);
        b = a;
        applyTransfers(b, rnd.next(1, 3), 15);
    } else if (mode == 3) {
        n = rnd.next(8, 25);
        a = randomArray(n, 20, 80);
        b = a;
        applyTransfers(b, rnd.next(n, 2 * n), 20);
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        a = randomArray(n, 1, 100);
        b = a;
        applyTransfers(b, rnd.next(n, 3 * n), 40);
    } else {
        n = 100;
        a = randomArray(n, 45, 55);
        b = a;
        applyTransfers(b, rnd.next(100, 180), 10);
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
