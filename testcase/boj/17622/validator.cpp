#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and k
    int N = inf.readInt(2, 50, "N");
    inf.readSpace();
    int k = inf.readInt(0, 1, "k");
    inf.readEoln();

    // 2. Read N lines of N integers (each in 0..5)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int tile = inf.readInt(0, 5, format("tile[%d][%d]", i+1, j+1).c_str());
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();
}
