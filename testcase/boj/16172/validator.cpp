#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read S
    string S = inf.readToken("[a-zA-Z0-9]{1,200000}", "S");
    inf.readEoln();

    // Read K
    string K = inf.readToken("[a-zA-Z]{1,200000}", "K");
    inf.readEoln();

    // Constraint: |K| <= |S|
    ensuref(K.size() <= S.size(), "Length of K (%zu) must be less than or equal to length of S (%zu)", K.size(), S.size());

    inf.readEof();
}
