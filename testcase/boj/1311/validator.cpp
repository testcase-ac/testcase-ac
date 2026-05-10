#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Read D matrix
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // Name for error message clarity
            string name = "D_" + to_string(i+1) + "_" + to_string(j+1);
            inf.readInt(1, 10000, name.c_str());
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();
}
