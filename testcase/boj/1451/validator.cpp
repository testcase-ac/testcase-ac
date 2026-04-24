#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions N and M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // There must be at least 3 cells in total
    ensuref((long long)N * M >= 3,
            "Total number of cells must be at least 3, but N=%d, M=%d gives %d",
            N, M, N * M);

    // Prepare a regex for a row: exactly M digits [0-9]
    string rowRegex = "[0-9]{" + to_string(M) + "}";

    // Read each of the N rows
    for (int i = 0; i < N; i++) {
        string rowName = "row_" + to_string(i);
        inf.readLine(rowRegex.c_str(), rowName.c_str());
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
