#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of trophies
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Heights of trophies
    for (int i = 0; i < N; i++) {
        inf.readInt(1, 100, "height");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
