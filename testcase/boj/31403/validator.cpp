#include "testlib.h"
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A
    string sA = inf.readLine("[1-9][0-9]{0,3}", "A");
    long long A = stoll(sA);
    ensuref(A >= 1 && A <= 1000, "Value of A out of allowed range [1,1000]: %lld", A);

    // Read B
    string sB = inf.readLine("[1-9][0-9]{0,3}", "B");
    long long B = stoll(sB);
    ensuref(B >= 1 && B <= 1000, "Value of B out of allowed range [1,1000]: %lld", B);

    // Read C
    string sC = inf.readLine("[1-9][0-9]{0,3}", "C");
    long long C = stoll(sC);
    ensuref(C >= 1 && C <= 1000, "Value of C out of allowed range [1,1000]: %lld", C);

    // No extra data after the third line
    inf.readEof();
    return 0;
}
