#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the string S: must be 1 to 100000 lowercase letters, no other chars.
    string S = inf.readLine("[a-z]{1,100000}", "S");

    // Read K on the next line: exactly a sequence of 1 to 6 digits (since K ≤ 100000),
    // no leading/trailing spaces.
    string Kline = inf.readLine("[0-9]{1,6}", "K");

    // Convert K to integer and check its bounds.
    long long K = 0;
    for (char c : Kline) {
        K = K * 10 + (c - '0');
        // We won't overflow because Kline has at most 6 digits.
    }
    ensuref(1 <= K && K <= 100000LL, "K must be between 1 and 100000; got %lld", K);

    // No extra content: exactly EOF now.
    inf.readEof();
    return 0;
}
