#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of straws
    int N = inf.readInt(3, 1000000, "N");
    inf.readEoln();

    // Read each straw length on its own line
    for (int i = 0; i < N; i++) {
        inf.readInt(1, 1000000, "straw_length");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
