#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of male students N and female students M
    int N = inf.readInt(2, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();
    
    inf.readEof();
    return 0;
}
