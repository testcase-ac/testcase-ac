#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose non-zero integer A
        int A;
        do { A = rnd.next(-5, 5); } while (A == 0);

        int type = rnd.next(0, 3);
        // roots
        int r1, r2, r3, a, b;
        long long B, C, D;
        if (type == 0) {
            // one integer root r1, two complex conjugate roots a ± bi
            r1 = rnd.next(-10, 10);
            // ensure non-zero imaginary part
            a = rnd.next(-5, 5);
            b = rnd.next(1, 5);
            // polynomial: A*(x - r1)*(x^2 - 2a x + (a^2 + b^2))
            // x^3 - (r1+2a)x^2 + (2a*r1 + a^2 + b^2)x - r1*(a^2+b^2)
            B = -1LL * A * (r1 + 2*a);
            C =  1LL * A * (2LL*a*r1 + 1LL*a*a + 1LL*b*b);
            D = -1LL * A * (1LL*r1*(1LL*a*a + 1LL*b*b));
        } else if (type == 1) {
            // three distinct integer real roots
            vector<int> vals;
            for (int x = -10; x <= 10; x++) vals.push_back(x);
            // pick 3 distinct
            shuffle(vals.begin(), vals.end());
            r1 = vals[0]; r2 = vals[1]; r3 = vals[2];
            // polynomial: A*(x - r1)*(x - r2)*(x - r3)
            // x^3 - (r1+r2+r3)x^2 + (r1r2+r1r3+r2r3)x - r1r2r3
            B = -1LL * A * (r1 + r2 + r3);
            C =  1LL * A * (1LL*r1*r2 + 1LL*r1*r3 + 1LL*r2*r3);
            D = -1LL * A * (1LL*r1*r2*r3);
        } else if (type == 2) {
            // double integer root r1, one integer root r2 distinct
            r1 = rnd.next(-10, 10);
            do { r2 = rnd.next(-10, 10); } while (r2 == r1);
            // polynomial: A*(x - r1)^2*(x - r2) = A*(x^2 - 2r1 x + r1^2)*(x - r2)
            // = x^3 - (2r1 + r2)x^2 + (r1^2 + 2r1*r2)x - r1^2*r2
            B = -1LL * A * (2LL*r1 + r2);
            C =  1LL * A * (1LL*r1*r1 + 2LL*r1*r2);
            D = -1LL * A * (1LL*r1*r1 * r2);
        } else {
            // triple integer root r1
            r1 = rnd.next(-10, 10);
            // polynomial: A*(x - r1)^3 = A*(x^3 - 3r1 x^2 + 3r1^2 x - r1^3)
            B = -1LL * A * (3LL*r1);
            C =  1LL * A * (3LL*r1*r1);
            D = -1LL * A * (1LL*r1*r1*r1);
        }
        // Output with 11 decimal places
        printf("%.11f %.11f %.11f %.11f\n",
               A * 1.0,
               B * 1.0,
               C * 1.0,
               D * 1.0);
    }
    return 0;
}
