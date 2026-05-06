#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // There is no test case count; input consists of a single integer n.
    // According to the statement: "n은 45보다 작거나 같은 자연수이다."
    // We interpret "자연수" as 1,2,3,...
    int n = inf.readInt(1, 45, "n");
    // No extra tokens on the line
    inf.readEoln();
    // End of file immediately after
    inf.readEof();
    return 0;
}
