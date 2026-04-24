#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of queries Q: 0 <= Q <= 100
    int Q = inf.readInt(0, 100, "Q");
    inf.readEoln();

    for (int i = 0; i < Q; i++) {
        // For each query, read S and E with 1 <= S <= E <= 2016
        int S = inf.readInt(1, 2016, ("S_" + to_string(i)).c_str());
        inf.readSpace();
        int E = inf.readInt(1, 2016, ("E_" + to_string(i)).c_str());
        ensuref(S <= E,
                "In query %d: start year S (%d) must be <= end year E (%d)",
                i + 1, S, E);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
