#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first string A: should consist of lowercase letters (possibly empty)
    string A = inf.readLine("[a-z]*", "A");
    // Read second string B: same constraints
    string B = inf.readLine("[a-z]*", "B");

    // Check the total length constraint: |A| + |B| <= 200000
    long long n = A.size();
    long long m = B.size();
    ensuref(n + m <= 200000,
            "The total length of A and B must be at most 200000, but got %d + %d = %d",
            n, m, n + m);

    // No extra content
    inf.readEof();
    return 0;
}
