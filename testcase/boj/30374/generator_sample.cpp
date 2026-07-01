#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long randomCost(int mode) {
    if (mode == 0) {
        return rnd.next(-10, 10);
    }
    if (mode == 1) {
        return rnd.next(-1000, 1000);
    }
    if (mode == 2) {
        vector<long long> choices = {-1000000000LL, -1000000LL, -1LL, 0LL, 1LL, 1000000LL, 1000000000LL};
        return choices[rnd.next((int)choices.size())];
    }
    if (rnd.next(0, 4) == 0) {
        return rnd.next(0, 1) == 0 ? -1000000000LL : 1000000000LL;
    }
    return rnd.next(-1000000000, 1000000000);
}

string randomParentheses(int n, int mode) {
    string s;
    s.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next(0, 1) == 0 ? '(' : ')');
        }
    } else if (mode == 1) {
        int openCount = rnd.next(0, n);
        s.append(openCount, '(');
        s.append(n - openCount, ')');
    } else if (mode == 2) {
        int closeCount = rnd.next(0, n);
        s.append(closeCount, ')');
        s.append(n - closeCount, '(');
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            s.push_back(i % 2 == 0 ? '(' : ')');
        }
        if (rnd.next(0, 1) == 1) {
            reverse(s.begin(), s.end());
        }
    } else if (mode == 4) {
        int balance = 0;
        for (int i = 0; i < n; ++i) {
            bool putOpen = balance == 0 || rnd.next(0, 99) < 55;
            if (putOpen) {
                s.push_back('(');
                ++balance;
            } else {
                s.push_back(')');
                --balance;
            }
        }
    } else {
        s.assign(n, rnd.next(0, 1) == 0 ? '(' : ')');
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 9);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 5) {
        n = rnd.next(2, 30);
    } else if (sizeMode <= 8) {
        n = rnd.next(31, 120);
    } else {
        n = rnd.next(1000, 300000);
    }

    int parenthesesMode = rnd.next(0, 5);
    int costMode = rnd.next(0, 3);

    string s = randomParentheses(n, parenthesesMode);
    vector<long long> costs(n);
    for (int i = 0; i < n; ++i) {
        costs[i] = randomCost(costMode);
    }

    cout << n << '\n';
    cout << s << '\n';
    println(costs);

    return 0;
}
