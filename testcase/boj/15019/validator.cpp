#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of players n and number of features k
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 20, "k");
    inf.readEoln();

    // Read each player's feature string
    for (int i = 0; i < n; i++) {
        string s = inf.readToken("[01]+", "features");
        // Check exact length k
        ensuref((int)s.size() == k,
                "Length of feature string at line %d is %d but expected %d", 
                i + 2, (int)s.size(), k);
        inf.readEoln();
    }

    // The file must end immediately after the last newline
    inf.readEof();
    return 0;
}
