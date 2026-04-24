#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // Read skill levels
    for (int i = 1; i <= N; i++) {
        inf.readInt(1, 100000, ("s_" + to_string(i)).c_str());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
