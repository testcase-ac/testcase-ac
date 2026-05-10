#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: p1, p2, p3, p4
    long long p1 = inf.readLong(-1000000000LL, 1000000000LL, "p1");
    inf.readSpace();
    long long p2 = inf.readLong(-1000000000LL, 1000000000LL, "p2");
    inf.readSpace();
    long long p3 = inf.readLong(-1000000000LL, 1000000000LL, "p3");
    inf.readSpace();
    long long p4 = inf.readLong(-1000000000LL, 1000000000LL, "p4");
    inf.readEoln();

    // Strictly increasing
    ensuref(p1 < p2, "p1 (%lld) must be < p2 (%lld)", p1, p2);
    ensuref(p2 < p3, "p2 (%lld) must be < p3 (%lld)", p2, p3);
    ensuref(p3 < p4, "p3 (%lld) must be < p4 (%lld)", p3, p4);

    // Second line: x, y, r
    long long x = inf.readLong(-1000000000LL, 1000000000LL, "x");
    inf.readSpace();
    long long y = inf.readLong(1LL, 1000000000LL, "y"); // y > 0
    inf.readSpace();
    long long r = inf.readLong(1LL, 1000000000LL, "r");
    inf.readEoln();

    // "사과가 x축 위에 떠 있다는 것이 보장된다" -> circle completely above x-axis
    // This means: y - r > 0  => y > r
    ensuref(y > r, "Apple must be strictly above x-axis: need y > r, got y=%lld, r=%lld", y, r);

    inf.readEof();
}
