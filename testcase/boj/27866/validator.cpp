#include "testlib.h"
#include <string>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate S: non-empty, up to 1000 chars, only A-Z or a-z
    string S = inf.readLine("[a-zA-Z]{1,1000}", "S");

    // Read and validate the second line as a pure digit string
    string Si = inf.readLine("[0-9]+", "i");

    // Parse Si into integer i, checking overflow relative to S.size()
    long long i = 0;
    for (char c : Si) {
        i = i * 10 + (c - '0');
        // At any point, i must not exceed |S|
        ensuref(i <= (long long)S.size(),
                "i (%lld) is greater than length of S (%d)", i, (int)S.size());
    }
    // Final bounds check: 1 <= i <= |S|
    ensuref(i >= 1, "i (%lld) is less than 1", i);

    // No more content
    inf.readEof();
    return 0;
}
