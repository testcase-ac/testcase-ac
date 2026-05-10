#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read L
    int L = inf.readInt(1, 3000000, "L");
    inf.readEoln();

    // 2. Read M_L and M_K
    int M_L = inf.readInt(1, 3000000, "M_L");
    inf.readSpace();
    int M_K = inf.readInt(1, 100, "M_K");
    inf.readEoln();

    // 3. Read C_ammo
    int C_ammo = inf.readInt(0, 3000000, "C_ammo");
    inf.readEoln();

    // 4. Read Z_i for i = 1..L
    for (int i = 1; i <= L; ++i) {
        int Z_i = inf.readInt(0, 300000000, "Z_i");
        inf.readEoln();
    }

    inf.readEof();
}
