#include "testlib.h"

using namespace std;

// Helper function to check if n is composite (i.e., not prime and >1)
bool is_composite(long long n) {
    if (n <= 3) return false;
    if (n % 2 == 0) return true;
    for (long long d = 3; d * d <= n && d <= 1000000; d += 2) {
        if (n % d == 0) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Only one integer N on a single line
    long long N = inf.readLong(2LL, 1000000000000LL, "N");
    inf.readEoln();
    inf.readEof();
}
