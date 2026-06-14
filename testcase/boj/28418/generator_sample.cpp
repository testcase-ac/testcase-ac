#include "testlib.h"
#include <array>
using namespace std;

using Coeffs = array<int, 5>;

long long discr(const Coeffs& v) {
    long long a = v[0], b = v[1], c = v[2], d = v[3], e = v[4];
    long long A = a * d * d - a * d;
    long long B = 2 * a * d * e;
    long long C = a * e * e + b * e + c - c * d - e;
    return B * B - 4 * A * C;
}

long long quadA(const Coeffs& v) {
    long long a = v[0], d = v[3];
    return a * d * d - a * d;
}

int nonzeroInt() {
    int x = rnd.next(-20, 19);
    return x >= 0 ? x + 1 : x;
}

Coeffs randomCase() {
    return {rnd.next(-20, 20), rnd.next(-20, 20), rnd.next(-20, 20),
            rnd.next(-20, 20), rnd.next(-20, 20)};
}

Coeffs findCase(bool (*ok)(const Coeffs&), Coeffs fallback) {
    for (int attempt = 0; attempt < 20000; ++attempt) {
        Coeffs v = randomCase();
        if (ok(v)) return v;
    }
    return fallback;
}

bool isTwoRoots(const Coeffs& v) {
    return quadA(v) != 0 && discr(v) > 0;
}

bool isDoubleRoot(const Coeffs& v) {
    return quadA(v) != 0 && discr(v) == 0;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    Coeffs v;

    if (mode == 0) {
        v = randomCase();
    } else if (mode == 1) {
        v = {0, 1, rnd.next(-20, 20), 1, rnd.next(-20, 20)};
    } else if (mode == 2) {
        int b = rnd.next(-20, 19);
        if (b >= 1) ++b;
        v = {0, b, rnd.next(-20, 20), 1, nonzeroInt()};
    } else if (mode == 3) {
        v = {nonzeroInt(), rnd.next(-20, 20), rnd.next(-20, 20), 1, nonzeroInt()};
    } else if (mode == 4) {
        v = findCase(isTwoRoots, {1, 1, 1, 5, 0});
    } else {
        v = findCase(isDoubleRoot, {2, 4, 0, 2, 0});
    }

    println(v[0], v[1], v[2]);
    println(v[3], v[4]);

    return 0;
}
