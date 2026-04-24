#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of chapters N and total study time T
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    // Read each chapter's required study time K and score S
    for (int i = 0; i < N; i++) {
        int K = inf.readInt(1, 1000, "K");
        inf.readSpace();
        int S = inf.readInt(1, 1000, "S");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
