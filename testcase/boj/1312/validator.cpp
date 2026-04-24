#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A, B, N as per problem constraints
    int A = inf.readInt(1, 100000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100000, "B");
    inf.readSpace();
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // No additional global constraints to verify for this problem
    
    inf.readEof();
    return 0;
}
