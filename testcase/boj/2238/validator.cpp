#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read U and N
    int U = inf.readInt(1, 10000, "U");
    inf.readSpace();
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read each of the N bids
    for (int i = 0; i < N; i++) {
        // Name: non-empty, <=10 chars, only A-Z or a-z, no spaces
        inf.readToken("[A-Za-z]{1,10}", "name");
        inf.readSpace();
        // Price: integer in [1, U]
        inf.readInt(1, U, "price");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
