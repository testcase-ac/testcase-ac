#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(N, 200000, "M"); // ensures M >= N
    inf.readEoln();

    // Read string A
    string A = inf.readToken("[A-Z]+", "A");
    ensuref((int)A.size() == N,
            "Length of string A is %d but expected %d", (int)A.size(), N);
    inf.readEoln();

    // Read string B
    string B = inf.readToken("[A-Z]+", "B");
    ensuref((int)B.size() == M,
            "Length of string B is %d but expected %d", (int)B.size(), M);
    inf.readEoln();

    // No further global constraints to check
    inf.readEof();
    return 0;
}
