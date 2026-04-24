#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of total keystrokes
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // No more content
    inf.readEof();
    return 0;
}
