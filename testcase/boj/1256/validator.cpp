#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K with exact whitespace format: "N M K\n"
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readSpace();
    long long K = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    // No further global constraints; K may exceed C(N+M, N) as per problem statement.

    inf.readEof();
    return 0;
}
