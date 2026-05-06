#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long LIM = 100000000LL;

    long long A = inf.readLong(-LIM, LIM, "A");
    inf.readSpace();
    long long B = inf.readLong(-LIM, LIM, "B");
    inf.readSpace();
    long long C = inf.readLong(-LIM, LIM, "C");
    inf.readSpace();
    long long x1 = inf.readLong(-LIM, LIM, "x1");
    inf.readSpace();
    long long x2 = inf.readLong(-LIM, LIM, "x2");
    inf.readSpace();
    long long y1 = inf.readLong(-LIM, LIM, "y1");
    inf.readSpace();
    long long y2 = inf.readLong(-LIM, LIM, "y2");
    inf.readEoln();

    ensuref(x1 <= x2, "Expected x1 <= x2, but got x1=%lld, x2=%lld", x1, x2);
    ensuref(y1 <= y2, "Expected y1 <= y2, but got y1=%lld, y2=%lld", y1, y2);

    // No additional global constraints implied by the problem:
    // it only bounds input integers and ranges.

    inf.readEof();
}
