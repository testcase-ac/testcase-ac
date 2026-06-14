#include "testlib.h"

#include <numeric>
#include <string>

using namespace std;

long long parsePart(const string& s, int begin, int end) {
    long long value = 0;
    for (int i = begin; i < end; ++i) {
        value = value * 10 + (s[i] - '0');
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The Korean BOJ statement and sample use one fraction line. The
    // English variant in the legacy artifact describes multiple test cases.
    string fraction = inf.readToken("[1-9][0-9]{0,9}/[1-9][0-9]{0,9}", "a/b");
    inf.readEoln();
    inf.readEof();

    int slash = fraction.find('/');
    long long a = parsePart(fraction, 0, slash);
    long long b = parsePart(fraction, slash + 1, fraction.size());

    ensuref(1 <= a && a <= 1000000000LL, "a is out of range: %lld", a);
    ensuref(1 <= b && b <= 1000000000LL, "b is out of range: %lld", b);
    ensuref(!(a == 1 && b == 1), "a and b must not both be 1");
    ensuref(gcd(a, b) == 1, "a and b must be coprime: %lld/%lld", a, b);

    int pathLength = 0;
    long long x = a;
    long long y = b;
    while (x != y) {
        ++pathLength;
        ensuref(pathLength <= 10000, "path length exceeds 10000 for %lld/%lld", a, b);

        if (x < y) {
            long long nextX = y - x;
            y = x;
            x = nextX;
        } else {
            long long nextY = x - y;
            x = y;
            y = nextY;
        }
    }
}
