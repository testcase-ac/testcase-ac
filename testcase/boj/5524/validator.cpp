#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of names
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        // Read a token consisting only of English letters, length 1..20
        string s = inf.readToken("[A-Za-z]{1,20}", "S_i");
        inf.readEoln();
        // No further constraints implied by the statement
    }

    inf.readEof();
}
