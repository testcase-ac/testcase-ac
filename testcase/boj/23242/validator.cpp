#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read B: number of buckets limit
    int B = inf.readInt(1, 30, "B");
    inf.readEoln();

    // Read n: number of data values
    int n = inf.readInt(1, 4000, "n");
    inf.readEoln();

    // Read frequencies f_i for i = 1..n
    for (int i = 1; i <= n; i++) {
        // frequencies are positive integers between 1 and 100 inclusive
        inf.readInt(1, 100, "f_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
