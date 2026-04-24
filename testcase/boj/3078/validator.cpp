#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(3, 300000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read N names, each must be 2..20 uppercase letters
    for (int i = 1; i <= N; i++) {
        inf.readToken("[A-Z]{2,20}", "name");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
