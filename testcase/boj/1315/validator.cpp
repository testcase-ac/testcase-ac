#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of quests N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read each quest's STR, INT, PNT
    for (int i = 0; i < N; i++) {
        int s = inf.readInt(1, 1000, "STR[i]");
        inf.readSpace();
        int intelligence = inf.readInt(1, 1000, "INT[i]");
        inf.readSpace();
        int p = inf.readInt(1, 1000, "PNT[i]");
        inf.readEoln();
    }

    // No more input
    inf.readEof();
    return 0;
}
