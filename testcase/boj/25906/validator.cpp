#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 100000, "T");
    inf.readSpace();
    inf.readInt(0, 100000, "K");
    inf.readEoln();

    vector<int> maxLevel(5);
    for (int skill = 0; skill < 5; ++skill) {
        maxLevel[skill] = inf.readInt(1, 100, "l_i");
        int previousAttack = 0;
        for (int level = 1; level <= maxLevel[skill]; ++level) {
            inf.readSpace();
            int attack = inf.readInt(1, 100000, "a_ij");
            ensuref(previousAttack <= attack,
                    "skill %d attack is decreasing at level %d: %d > %d",
                    skill + 1,
                    level,
                    previousAttack,
                    attack);
            previousAttack = attack;
        }
        inf.readEoln();
    }

    for (int kind = 0; kind < 3; ++kind) {
        int itemCount = inf.readInt(1, 50, "M");
        inf.readEoln();

        inf.readInts(itemCount, 1, 100000, "c_i");
        inf.readEoln();

        for (int item = 0; item < itemCount; ++item) {
            for (int skill = 0; skill < 5; ++skill) {
                if (skill > 0) {
                    inf.readSpace();
                }
                inf.readInt(0, maxLevel[skill], "v_ij");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
