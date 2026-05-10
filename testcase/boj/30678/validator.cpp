#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Only one integer N on a single line
    int N = inf.readInt(0, 5, "N");
    inf.readEoln();

    inf.readEof();
}
