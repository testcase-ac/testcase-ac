#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read pattern A: non-empty, lowercase letters only, length ≤ 25
    string A = inf.readLine("[a-z]+", "A");
    ensuref((int)A.size() <= 25,
            "Length of A must be at most 25, found %d", (int)A.size());

    // Read text T: lowercase letters only (possibly empty), length ≤ 300000
    string T = inf.readLine("[a-z]*", "T");
    ensuref((int)T.size() <= 300000,
            "Length of T must be at most 300000, found %d", (int)T.size());

    // No extra data after the two lines
    inf.readEof();
    return 0;
}
