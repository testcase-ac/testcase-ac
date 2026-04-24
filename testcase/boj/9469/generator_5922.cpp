#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int P = rnd.next(3, 7);
    printf("%d\n", P);
    for (int i = 1; i <= P; i++) {
        // Generate D with optional decimals
        bool decD = rnd.next(0, 1);
        int Dmult;
        if (!decD) {
            int Dint = rnd.next(10, 1000);
            Dmult = Dint * 100;
        } else {
            // from 10.00 to 1000.00 in hundredths
            Dmult = rnd.next(1000, 100000);
        }
        double D = Dmult / 100.0;

        // Decide if speeds A,B,F have decimals
        bool speedDec = rnd.next(0, 1);
        double A, B, F;
        if (!speedDec) {
            int Aint = rnd.next(1, 40);
            int Bint = rnd.next(Aint, 40);
            int Fint = rnd.next(Bint + 1, 50);
            A = Aint; B = Bint; F = Fint;
        } else {
            // A, B with two-decimal precision, ensuring B <= 39.99
            int Aint = rnd.next(1, 39);
            int Bint = rnd.next(Aint, 39);
            int Adec = rnd.next(0, 99);
            int Bdec = rnd.next(0, 99);
            int Amult = Aint * 100 + Adec;
            int Bmult = Bint * 100 + Bdec;
            if (Bmult < Amult) swap(Amult, Bmult);
            // F must be > Bmult/100 and ≤ 50.00
            int Fmult = rnd.next(Bmult + 1, 5000);
            A = Amult / 100.0;
            B = Bmult / 100.0;
            F = Fmult / 100.0;
        }

        // Output test case
        printf("%d %.2f %.2f %.2f %.2f\n", i, D, A, B, F);
    }
    return 0;
}
