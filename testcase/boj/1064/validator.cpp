#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read six integers: xA, yA, xB, yB, xC, yC
    vector<int> v = inf.readInts(6, -5000, 5000, "coord");
    inf.readEoln();

    // Points must be pairwise distinct as per problem statement
    // A = (v[0], v[1]), B = (v[2], v[3]), C = (v[4], v[5])
    ensuref(!(v[0] == v[2] && v[1] == v[3]),
            "Points A and B coincide: A=(%d,%d), B=(%d,%d)",
            v[0], v[1], v[2], v[3]);
    ensuref(!(v[0] == v[4] && v[1] == v[5]),
            "Points A and C coincide: A=(%d,%d), C=(%d,%d)",
            v[0], v[1], v[4], v[5]);
    ensuref(!(v[2] == v[4] && v[3] == v[5]),
            "Points B and C coincide: B=(%d,%d), C=(%d,%d)",
            v[2], v[3], v[4], v[5]);

    inf.readEof();
    return 0;
}
