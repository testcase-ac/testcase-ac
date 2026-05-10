#include "testlib.h"
#include <vector>
using namespace std;

bool is_prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and P on the first line
    int N = inf.readInt(0, 1000000, "N");
    inf.readSpace();
    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    // P must be prime (note: 1 is not prime)
    ensuref(P >= 2, "P must be prime but P = %d", P);
    ensuref(is_prime(P), "P is not prime: %d", P);

    // Read coefficients a_N, ..., a_0
    vector<long long> a = inf.readLongs((long long)N + 1, 0LL, 1000000000LL, "a_i");
    inf.readEoln();

    // No more content
    inf.readEof();
    return 0;
}
