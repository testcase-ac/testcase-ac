#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(7, 100, "a");
    inf.readSpace();
    int b = inf.readInt(7, 100, "b");
    inf.readSpace();
    long long c = inf.readLong(1LL, 1000000000LL, "c");
    inf.readSpace();
    long long d = inf.readLong(1LL, 1000000000LL, "d");
    inf.readSpace();
    long long e = inf.readLong(1LL, 1000000000LL, "e");
    inf.readSpace();
    long long f = inf.readLong(1LL, 1000000000LL, "f");
    inf.readSpace();
    long long g = inf.readLong(1LL, 1000000000LL, "g");
    inf.readEoln();
    inf.readEof();

    ensuref(a <= b, "sheet dimensions must satisfy a <= b, got %d > %d", a, b);
    ensuref(f < g, "range endpoints must satisfy f < g, got %lld >= %lld", f, g);

    vector<long long> sizes;
    for (int cut = 1; 2 * cut < a && 2 * cut < b; ++cut) {
        sizes.push_back(1LL * cut * (a - 2 * cut) * (b - 2 * cut));
    }
    sort(sizes.begin(), sizes.end(), greater<long long>());
    ensuref(sizes.size() >= 3,
            "sheet dimensions must allow at least three positive integer box sizes");

    long long s1 = sizes[0];
    long long s2 = sizes[1];
    long long s3 = sizes[2];

    ensuref(c < s1, "c must be a remainder modulo the largest box size %lld", s1);
    ensuref(d < s2, "d must be a remainder modulo the second largest box size %lld", s2);
    ensuref(e < s3, "e must be a remainder modulo the third largest box size %lld", s3);

    int answers = 0;
    for (long long n = f + ((c - f % s1 + s1) % s1); n <= g; n += s1) {
        if (n % s2 == d && n % s3 == e) {
            ++answers;
        }
        ensuref(answers <= 1, "more than one shipment total satisfies the remainders");
    }
    ensuref(answers == 1, "expected exactly one shipment total satisfying all remainders");
}
