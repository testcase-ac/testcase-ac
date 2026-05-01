#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

struct Triple {
    int a, b, c;
};

// Generate (a, b, c) for d = 0 (so c must be 0), gcd(a,b,c)=1 and |a|,|b| ≤ 10
Triple genTripleD0(bool allowZero, bool preferSimple) {
    while (true) {
        if (allowZero && rnd.next(0, 4) == 0) { // 20% chance of exact zero (1,0,0)
            return {1, 0, 0};
        }
        int maxA = preferSimple ? 3 : 10;
        int maxB = preferSimple ? 5 : 10;

        int a = rnd.next(1, maxA);
        int b = rnd.next(-maxB, maxB);

        int g = std::gcd(a, std::abs(b));
        a /= g;
        b /= g;

        if (!allowZero && b == 0) continue; // avoid zero when we don't allow it

        return {a, b, 0};
    }
}

// Generate (a, b, c) for d > 0 (so c != 0), gcd(a,b,c)=1 and |a|,|b|,|c| ≤ 10
Triple genTripleDpos(bool preferSimple) {
    int maxA = preferSimple ? 3 : 10;
    int maxB = preferSimple ? 5 : 10;
    int maxC = preferSimple ? 5 : 10;

    while (true) {
        int a = rnd.next(1, maxA);
        int b = rnd.next(-maxB, maxB);
        int c = rnd.next(-maxC, maxC);
        if (c == 0) continue; // must have c != 0 when d > 0

        int g = std::gcd(a, std::gcd(std::abs(b), std::abs(c)));
        a /= g;
        b /= g;
        c /= g;

        return {a, b, c};
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Allowed d values: 0 or positive squarefree != 1, ≤ 10
    const int ds[7] = {0, 2, 3, 5, 6, 7, 10};
    int d = ds[rnd.next(0, 6)];
    bool dZero = (d == 0);

    bool preferSimpleA = (rnd.next(0, 1) == 0);
    bool preferSimpleB = (rnd.next(0, 1) == 0);

    Triple A0, A1, B0, B1;

    if (dZero) {
        // d = 0: pure rationals, c must be 0, and c=0 iff d=0 holds automatically
        A0 = genTripleD0(true, preferSimpleA);
        A1 = genTripleD0(true, preferSimpleA);

        // Generate B with B != 0
        while (true) {
            B0 = genTripleD0(true, preferSimpleB);
            B1 = genTripleD0(true, preferSimpleB);
            bool realZero = (B0.a == 1 && B0.b == 0); // represents 0
            bool imagZero = (B1.a == 1 && B1.b == 0);
            if (!(realZero && imagZero)) break;
        }
    } else {
        // d > 0: quadratic irrational parts, c must be != 0
        A0 = genTripleDpos(preferSimpleA);
        A1 = genTripleDpos(preferSimpleA);

        int relType = rnd.next(0, 3); // 0: random B, 1: B=A, 2: B=conj(A), 3: B=swap parts
        if (relType == 0) {
            B0 = genTripleDpos(preferSimpleB);
            B1 = genTripleDpos(preferSimpleB);
        } else if (relType == 1) {
            B0 = A0;
            B1 = A1;
        } else if (relType == 2) {
            B0 = A0;
            B1 = {A1.a, -A1.b, -A1.c}; // negate imaginary component
        } else { // relType == 3
            B0 = A1;
            B1 = A0; // swap real and imaginary parts
        }
        // For d > 0, each part is non-zero value, so B != 0 automatically.
    }

    // Output A
    {
        vector<int> line = {
            A0.a, A0.b, A0.c, d,
            A1.a, A1.b, A1.c, d
        };
        println(line);
    }

    // Output B
    {
        vector<int> line = {
            B0.a, B0.b, B0.c, d,
            B1.a, B1.b, B1.c, d
        };
        println(line);
    }

    return 0;
}
