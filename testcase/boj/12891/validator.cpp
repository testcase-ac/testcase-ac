#include "testlib.h"
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read lengths S and P
    int S = inf.readInt(1, 1000000, "S");
    inf.readSpace();
    int P = inf.readInt(1, S, "P");
    inf.readEoln();

    // Read DNA string of length S, only characters A, C, G, T
    string dna = inf.readToken("[ACGT]+", "dna");
    ensuref((int)dna.length() == S,
            "Length of DNA string (%d) does not match S (%d)", (int)dna.length(), S);
    inf.readEoln();

    // Read required minimum counts for A, C, G, T
    vector<int> req = inf.readInts(4, 0, S, "reqCnt");
    inf.readEoln();

    // Sum of requirements must not exceed S
    long long sumReq = 0;
    for (int x : req) {
        sumReq += x;
    }
    ensuref(sumReq <= S,
            "Sum of required counts (%lld) exceeds S (%d)", sumReq, S);

    inf.readEof();
    return 0;
}
