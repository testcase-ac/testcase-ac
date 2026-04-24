#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and ensure it's between 1 and 64
    int N = inf.readInt(1, 64, "N");
    inf.readEoln();

    // Ensure N is a power of two
    ensuref((N & (N - 1)) == 0,
            "N=%d is not a power of two", N);

    // Read N lines, each must be exactly length N and consist only of '0' or '1'
    for (int i = 0; i < N; i++) {
        // Read one line of 0/1 characters
        string row = inf.readLine("[01]{1,64}", "row");
        // Check its length matches N
        ensuref((int)row.length() == N,
                "Line %d length %d is not equal to N=%d",
                i+1, (int)row.length(), N);
    }

    inf.readEof();
    return 0;
}
