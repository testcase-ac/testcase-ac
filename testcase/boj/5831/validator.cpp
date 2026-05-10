#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and B
    int N = inf.readInt(3, 16, "N");
    inf.readSpace();
    long long B = inf.readLong(1LL, 1000000000000000LL, "B");
    inf.readEoln();

    // Read N lines, each with a single integer 0 or 1
    for (int i = 0; i < N; ++i) {
        int state = inf.readInt(0, 1, ("state_" + to_string(i+1)).c_str());
        inf.readEoln();
    }

    inf.readEof();
}
