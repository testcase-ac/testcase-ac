#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> balances;
    int j;
    int c;

    if (mode == 0) {
        n = 1;
        balances = {rnd.next(1, 20)};
        j = rnd.next(1, 20);
        c = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        balances.assign(n, 0);
        balances[rnd.next(n)] = rnd.next(1, 100000);
        j = rnd.any(vector<int>{1, 2, 1000});
        c = rnd.next(1, 30);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        int common = rnd.next(1, 30);
        balances.assign(n, common);
        j = rnd.next(1, 100);
        c = rnd.next(1, 100);
    } else if (mode == 3) {
        n = rnd.next(2, 15);
        balances.resize(n);
        for (int i = 0; i < n; ++i) {
            balances[i] = rnd.next(0, 50);
        }
        if (balances[0] == 0 && rnd.next(2) == 0) {
            balances[0] = rnd.next(1, 10);
        }
        j = rnd.next(1, 250);
        c = rnd.next(1, 250);
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        balances.resize(n);
        balances[0] = rnd.next(0, 5);
        for (int i = 1; i < n; ++i) {
            balances[i] = rnd.next(50000, 100000);
        }
        j = rnd.next(500, 1000);
        c = rnd.next(500, 1000);
    } else if (mode == 5) {
        n = 50;
        balances.resize(n);
        for (int i = 0; i < n; ++i) {
            balances[i] = rnd.next(0, 100000);
        }
        j = rnd.next(1, 1000);
        c = rnd.next(1, 1000);
    } else {
        n = rnd.next(2, 20);
        balances.resize(n);
        int cap = rnd.any(vector<int>{3, 10, 100, 1000});
        for (int i = 0; i < n; ++i) {
            balances[i] = rnd.wnext(cap + 1, -2);
        }
        j = rnd.any(vector<int>{1, rnd.next(2, 100), 1000});
        c = rnd.any(vector<int>{1, rnd.next(2, 100), 1000});
    }

    long long total = 0;
    for (int balance : balances) {
        total += balance;
    }
    if (total == 0) {
        balances[rnd.next(n)] = 1;
    }

    println(n);
    println(balances);
    println(j);
    println(c);

    return 0;
}
