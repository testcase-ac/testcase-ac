#include "testlib.h"
#include <vector>

using namespace std;

int chooseX() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 0;
    if (mode == 1) return 1;
    if (mode == 2) return rnd.next(2, 10);
    if (mode == 3) return rnd.next(99999990, 100000000);
    if (mode == 4) return rnd.next(0, 1000);
    return rnd.next(0, 100000000);
}

vector<int> buildCoefficients(int n) {
    int mode = rnd.next(0, 5);
    vector<int> coefficients(n + 1);

    for (int i = 0; i <= n; ++i) {
        if (mode == 0) {
            coefficients[i] = rnd.next(0, 100);
        } else if (mode == 1) {
            coefficients[i] = rnd.next(90, 100);
        } else if (mode == 2) {
            coefficients[i] = (rnd.next(0, 4) == 0) ? rnd.next(1, 100) : 0;
        } else if (mode == 3) {
            coefficients[i] = (i % 2 == 0) ? rnd.next(0, 10) : rnd.next(90, 100);
        } else if (mode == 4) {
            coefficients[i] = rnd.next(0, 1) * 100;
        } else {
            coefficients[i] = (i == 0 || i == n) ? rnd.next(1, 100) : rnd.next(0, 100);
        }
    }

    return coefficients;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 6);
    } else if (sizeMode == 2) {
        n = rnd.next(7, 20);
    } else if (sizeMode == 3) {
        n = rnd.next(21, 60);
    } else {
        n = rnd.next(61, 120);
    }

    int x = chooseX();
    vector<int> coefficients = buildCoefficients(n);

    println(n, x);
    for (int degree = n; degree >= 0; --degree) {
        println(coefficients[n - degree], degree);
    }

    return 0;
}
