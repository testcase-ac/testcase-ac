#include "testlib.h"
#include <vector>

using namespace std;

struct Coeff {
    int a;
    int b;
    int c;
};

bool valid(const Coeff& e) {
    return e.a >= -100 && e.a <= 100 && e.a != 0 &&
           e.b >= -100 && e.b <= 100 && e.b != 0 &&
           e.c >= -100 && e.c <= 100 && e.c != 0;
}

Coeff fromRoots(int a, int r1, int r2) {
    return {a, -a * (r1 + r2), a * r1 * r2};
}

Coeff anyOf(const vector<Coeff>& choices) {
    return rnd.any(choices);
}

Coeff leeRootCase() {
    vector<Coeff> choices;
    vector<int> powers = {2, 4, 8, 16, 32, 64};

    for (int r1 : powers) {
        for (int r2 : powers) {
            if (r1 == r2) continue;
            for (int a = -100; a <= 100; ++a) {
                if (a == 0) continue;
                Coeff e = fromRoots(a, r1, r2);
                if (valid(e)) choices.push_back(e);
            }
        }
    }

    return anyOf(choices);
}

Coeff integerRootCase() {
    vector<Coeff> choices;

    for (int r1 = -10; r1 <= 10; ++r1) {
        for (int r2 = -10; r2 <= 10; ++r2) {
            if (r1 == r2) continue;
            bool r1Lee = r1 > 1 && (r1 & (r1 - 1)) == 0;
            bool r2Lee = r2 > 1 && (r2 & (r2 - 1)) == 0;
            if (r1Lee && r2Lee) continue;
            for (int a = -12; a <= 12; ++a) {
                if (a == 0) continue;
                Coeff e = fromRoots(a, r1, r2);
                if (valid(e)) choices.push_back(e);
            }
        }
    }

    return anyOf(choices);
}

Coeff repeatedRootCase() {
    vector<Coeff> choices;

    for (int r = -10; r <= 10; ++r) {
        for (int a = -20; a <= 20; ++a) {
            if (a == 0) continue;
            Coeff e = fromRoots(a, r, r);
            if (valid(e)) choices.push_back(e);
        }
    }

    return anyOf(choices);
}

Coeff negativeDiscriminantCase() {
    vector<Coeff> choices;

    for (int a = -10; a <= 10; ++a) {
        if (a == 0) continue;
        for (int b = -30; b <= 30; ++b) {
            if (b == 0) continue;
            for (int c = -20; c <= 20; ++c) {
                if (c == 0) continue;
                int d = b * b - 4 * a * c;
                if (d < 0) choices.push_back({a, b, c});
            }
        }
    }

    return anyOf(choices);
}

Coeff randomCoefficientCase() {
    while (true) {
        Coeff e = {rnd.next(-100, 100), rnd.next(-100, 100), rnd.next(-100, 100)};
        if (valid(e)) return e;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    Coeff e;
    if (mode == 0) {
        e = leeRootCase();
    } else if (mode == 1) {
        e = integerRootCase();
    } else if (mode == 2) {
        e = repeatedRootCase();
    } else if (mode == 3) {
        e = negativeDiscriminantCase();
    } else {
        e = randomCoefficientCase();
    }

    println(e.a, e.b, e.c);
    return 0;
}
