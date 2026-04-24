#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(5, 20, "N");
    inf.readEoln();

    // Read the grid A of size N x N
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Name each cell for clearer error messages
            char name[32];
            snprintf(name, sizeof(name), "A_%d_%d", i+1, j+1);
            inf.readInt(1, 100, name);
            if (j < N-1) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
