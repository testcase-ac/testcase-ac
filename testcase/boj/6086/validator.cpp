#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of pipes
    int N = inf.readInt(1, 700, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        // Read first node (single uppercase or lowercase letter)
        string u = inf.readToken("[A-Za-z]", "a_i");
        inf.readSpace();
        // Read second node
        string v = inf.readToken("[A-Za-z]", "b_i");
        inf.readSpace();
        // Read capacity
        int f = inf.readInt(1, 1000, "F_i");
        inf.readEoln();

        // The two endpoints must be different
        ensuref(u != v,
                "Pipe %d has same endpoints '%s' and '%s'", 
                i + 1, u.c_str(), v.c_str());
    }

    inf.readEof();
    return 0;
}
