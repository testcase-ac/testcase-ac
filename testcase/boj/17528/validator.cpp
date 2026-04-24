#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of tasks
    int n = inf.readInt(1, 250, "n");
    inf.readEoln();

    // For each task, read a_i and b_i
    for (int i = 0; i < n; i++) {
        int a = inf.readInt(1, 250, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, 250, "b_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
