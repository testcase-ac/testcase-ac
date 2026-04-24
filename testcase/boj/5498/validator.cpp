#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of jobs
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Batch setup time
    int S = inf.readInt(0, 50, "S");
    inf.readEoln();

    // Each job: processing time T_i and cost factor F_i
    for (int i = 1; i <= N; i++) {
        // T_i: 1 ≤ T_i ≤ 100
        string tName = "T_" + to_string(i);
        int T = inf.readInt(1, 100, tName);

        inf.readSpace();

        // F_i: 1 ≤ F_i ≤ 100
        string fName = "F_" + to_string(i);
        int F = inf.readInt(1, 100, fName);

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
