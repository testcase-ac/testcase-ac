#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int G = 5; // number of games / lines

    for (int i = 1; i <= G; ++i) {
        int Ai = inf.readInt(0, 100, "A_i");
        if (i < G) {
            inf.readEoln();
        } else {
            // last line, after it we expect EOF (checked below)
            inf.readEoln();
        }
    }

    inf.readEof();
}
