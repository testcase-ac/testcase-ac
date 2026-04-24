#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students N and number of power strips K
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100, "K");
    inf.readEoln();

    // Read the number of outlets on each power strip
    vector<int> A = inf.readInts(K, 3, 8, "A");
    inf.readEoln();

    // No further global constraints to check -- problem allows any configuration
    inf.readEof();
    return 0;
}
