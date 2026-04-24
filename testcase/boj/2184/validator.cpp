#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and factory location L
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int L = inf.readInt(1, 1000000, "L");
    inf.readEoln();

    // Read the N city coordinates
    for (int i = 1; i <= N; i++) {
        string name = "x_" + to_string(i);
        inf.readInt(1, 1000000, name.c_str());
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
