#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement omits a lower bound, but N is the number of people in a meeting.
    int n = inf.readInt(2, 10000, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even: %d", n);
    inf.readEof();
}
