#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

vector<int> sparseCounts() {
    vector<int> x(9, 0);
    int active = rnd.next(1, 4);
    vector<int> digits(9);
    iota(digits.begin(), digits.end(), 0);
    shuffle(digits.begin(), digits.end());

    int remaining = rnd.next(2, 25);
    for (int i = 0; i < active; ++i) {
        int give = (i + 1 == active) ? remaining : rnd.next(0, remaining);
        x[digits[i]] = give;
        remaining -= give;
    }
    if (accumulate(x.begin(), x.end(), 0) < 2) {
        x[digits[0]] += 2 - accumulate(x.begin(), x.end(), 0);
    }
    return x;
}

vector<int> balancedCounts() {
    vector<int> x(9, 0);
    int total = rnd.next(9, 80);
    for (int i = 0; i < total; ++i) {
        ++x[rnd.next(9)];
    }
    return x;
}

vector<int> singleDigitCounts() {
    vector<int> x(9, 0);
    x[rnd.next(9)] = rnd.next(2, 120);
    return x;
}

vector<int> sixNineHeavyCounts() {
    vector<int> x(9, 0);
    int total = rnd.next(2, 180);
    for (int i = 0; i < total; ++i) {
        int pick = rnd.next(100);
        if (pick < 45) {
            ++x[5];
        } else if (pick < 90) {
            ++x[8];
        } else {
            ++x[rnd.next(9)];
        }
    }
    return x;
}

vector<int> largeCounts() {
    vector<int> x(9, 0);
    int total = rnd.next(850, 1000);
    int biasDigit = rnd.next(9);
    for (int i = 0; i < total; ++i) {
        if (rnd.next(100) < 65) {
            ++x[biasDigit];
        } else {
            ++x[rnd.next(9)];
        }
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 50);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(100);
        vector<int> x;
        if (mode < 25) {
            x = sparseCounts();
        } else if (mode < 50) {
            x = balancedCounts();
        } else if (mode < 68) {
            x = singleDigitCounts();
        } else if (mode < 90) {
            x = sixNineHeavyCounts();
        } else {
            x = largeCounts();
        }
        println(x);
    }

    return 0;
}
