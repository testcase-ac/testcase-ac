#include "testlib.h"
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int DH = inf.readInt(1, 1000, "DH");
        inf.readSpace();
        int DS = inf.readInt(1, 1000, "DS");
        inf.readSpace();
        int HD = inf.readInt(1, 1000, "HD");
        inf.readSpace();
        int HS = inf.readInt(1, 1000, "HS");
        inf.readSpace();
        int SD = inf.readInt(1, 1000, "SD");
        inf.readSpace();
        int SH = inf.readInt(1, 1000, "SH");
        inf.readEoln();

        // Each pair is guaranteed to be coprime (mutually prime).
        ensuref(std::gcd(DH, DS) == 1,
                "In test %d, DH and DS are not coprime: gcd(%d, %d) = %d",
                tc + 1, DH, DS, std::gcd(DH, DS));
        ensuref(std::gcd(HD, HS) == 1,
                "In test %d, HD and HS are not coprime: gcd(%d, %d) = %d",
                tc + 1, HD, HS, std::gcd(HD, HS));
        ensuref(std::gcd(SD, SH) == 1,
                "In test %d, SD and SH are not coprime: gcd(%d, %d) = %d",
                tc + 1, SD, SH, std::gcd(SD, SH));

        // At least one friend participates in each vote for every person.
        // Let k1, k2, k3 be positive integers (number of "blocks" of the ratio)
        // Then counts are:
        //   H_from_D = DH * k1,  S_from_D = DS * k1
        //   D_from_H = HD * k2,  S_from_H = HS * k2
        //   D_from_S = SD * k3,  H_from_S = SH * k3
        //
        // Requirement: each vote has at least 1 participant:
        //   DH*k1 + DS*k1 >= 1  => k1 >= 1 (holds for any positive k1 since DH,DS>=1)
        // similarly for k2, k3.
        // Because all given numbers are >=1, existence of such positive integers
        // is automatic; no extra checks needed beyond given ranges.
    }

    inf.readEof();
}
