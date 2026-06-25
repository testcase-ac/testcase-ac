#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomLetter(int n, int alphabetSize) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += static_cast<char>('A' + rnd.next(alphabetSize));
    }
    return s;
}

void printSwapRule(int n) {
    int i = rnd.next(0, n - 1);
    int j = rnd.next(0, n - 2);
    if (j >= i) ++j;
    println("S", i, j);
}

void printAddRule(int n) {
    println("A", rnd.next(0, n - 1), rnd.next(1, 25));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int c;
    long long k;
    int alphabetSize;

    if (mode == 0) {
        n = 1;
        c = rnd.next(1, 12);
        k = rnd.any(vector<long long>{1LL, 2LL, 25LL, 26LL, 1000000000000LL});
        alphabetSize = rnd.next(1, 26);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        c = rnd.next(n, n + 8);
        k = 1'000'000'000'000LL - rnd.next(0, 1000);
        alphabetSize = rnd.next(2, 26);
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        c = rnd.next(1, 40);
        k = 1LL * c * rnd.next(1, 1000000);
        alphabetSize = rnd.any(vector<int>{1, 2, 3, 26});
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        c = rnd.next(1, 35);
        k = rnd.next(1LL, 2LL * c + 10);
        alphabetSize = rnd.next(2, 8);
    } else {
        n = rnd.next(2, 30);
        c = rnd.next(1, 45);
        k = rnd.next(1LL, 1000000000000LL);
        alphabetSize = rnd.next(2, 26);
    }

    println(n, c, k);
    println(randomLetter(n, alphabetSize));

    for (int rule = 0; rule < c; ++rule) {
        if (n == 1) {
            printAddRule(n);
        } else if (mode == 1) {
            if (rule % 3 == 2) {
                printAddRule(n);
            } else {
                printSwapRule(n);
            }
        } else if (mode == 2) {
            if (rnd.next(0, 4) == 0) {
                printSwapRule(n);
            } else {
                printAddRule(n);
            }
        } else if (mode == 3) {
            if (rule % 2 == 0) {
                println("A", rnd.next(0, n - 1), rnd.any(vector<int>{1, 13, 25}));
            } else {
                printSwapRule(n);
            }
        } else {
            if (rnd.next(0, 1) == 0) {
                printSwapRule(n);
            } else {
                printAddRule(n);
            }
        }
    }

    return 0;
}
