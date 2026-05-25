#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound; this cap keeps inputs finite
    // and within the existing reference solution's int arithmetic.
    const long long max_boxes = 100000000LL;

    long long r = inf.readLong(0LL, max_boxes, "R");
    inf.readEoln();
    long long s = inf.readLong(0LL, max_boxes, "S");
    inf.readEoln();

    long long total = 8 * r + 3 * s;
    ensuref(total >= 28, "total cupcakes must be at least 28, got %lld", total);

    inf.readEof();
}
