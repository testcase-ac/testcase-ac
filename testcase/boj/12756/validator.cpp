#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Player A's card: attack and health
    int a_atk = inf.readInt(1, 100000, "A_attack");
    inf.readSpace();
    int a_hp  = inf.readInt(1, 100000, "A_health");
    inf.readEoln();

    // Player B's card: attack and health
    int b_atk = inf.readInt(1, 100000, "B_attack");
    inf.readSpace();
    int b_hp  = inf.readInt(1, 100000, "B_health");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
