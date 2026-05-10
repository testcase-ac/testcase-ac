#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Prepare regex for DNA strings of length M over {A,C,G,T}
    string dna_regex = "[ACGT]{" + to_string(M) + "}";

    // Read and validate each DNA string
    for (int i = 0; i < N; i++) {
        string name = "s_" + to_string(i+1);
        inf.readToken(dna_regex.c_str(), name.c_str());
        inf.readEoln();
    }

    // No extra characters after the last line
    inf.readEof();
    return 0;
}
