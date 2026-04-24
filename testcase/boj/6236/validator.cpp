#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // Read daily expenses
    for (int i = 0; i < N; i++) {
        inf.readInt(1, 10000, "expense_i");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
