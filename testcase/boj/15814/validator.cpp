#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the initial string S: length between 1 and 100, only letters and hyphens
    string S = inf.readToken("[A-Za-z\\-]{1,100}", "S");
    inf.readEoln();
    int N = (int)S.size();

    // Read T: number of swaps, natural number up to 50
    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    // Read T pairs of indices A, B
    for (int i = 0; i < T; i++) {
        int A = inf.readInt(0, N-1, "A_i");
        inf.readSpace();
        int B = inf.readInt(0, N-1, "B_i");
        inf.readEoln();
        // Swapping same index is allowed; no further checks needed
    }

    inf.readEof();
    return 0;
}
