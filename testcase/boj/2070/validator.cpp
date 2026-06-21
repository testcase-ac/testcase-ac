#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The Korean BOJ statement and official samples define one scenario;
    // the bundled English variant mentions a test count, which does not match this problem.
    inf.readToken("[01]{1,100}", "S");
    inf.readEoln();

    inf.readEof();
    return 0;
}
