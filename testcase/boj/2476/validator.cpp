#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of participants
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // For each participant, read three dice throws
    for (int i = 0; i < N; i++) {
        vector<int> d = inf.readInts(3, 1, 6, "dice");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
