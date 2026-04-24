#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of participants
    long long N = inf.readLong(1, 1000000000LL, "N");
    inf.readEoln();

    // Read counts for each T-shirt size
    static const char* sizeNames[6] = {"S", "M", "L", "XL", "XXL", "XXXL"};
    long long sumSizes = 0;
    for (int i = 0; i < 6; i++) {
        long long cnt = inf.readLong(0, N, sizeNames[i]);
        sumSizes += cnt;
        if (i < 5) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }
    ensuref(sumSizes == N,
            "Sum of T-shirt requests %lld does not equal N=%lld",
            sumSizes, N);

    // Read bundle sizes T and P
    long long T = inf.readLong(2, 1000000000LL, "T");
    inf.readSpace();
    long long P = inf.readLong(2, 1000000000LL, "P");
    inf.readEoln();

    inf.readEof();
    return 0;
}
