#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: a natural number (i.e., positive integer) up to 2,000,000
    int N = inf.readInt(1, 2000000, "N");
    
    // Ensure end of line after N and then EOF
    inf.readEoln();
    inf.readEof();

    return 0;
}
