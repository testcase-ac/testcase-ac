#include "testlib.h"

#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5, "N");
    inf.readSpace();
    int hp = inf.readInt(1, 100000, "HP");
    inf.readEoln();

    int minDamage = (hp + 9) / 10;
    int damageSum = 0;
    set<int> cooldowns;

    for (int i = 0; i < n; ++i) {
        int c = inf.readInt(1, 10, "C");
        inf.readSpace();
        int d = inf.readInt(minDamage, hp, "D");
        inf.readEoln();

        ensuref(cooldowns.insert(c).second,
                "cooldown values must be distinct, repeated C=%d at skill %d",
                c, i + 1);
        damageSum += d;
    }

    ensuref(damageSum < hp, "sum of damages must be less than HP: sum=%d HP=%d",
            damageSum, hp);

    inf.readEof();
}
