#include "testlib.h"
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line: two integers separated by a colon, no spaces.
    // We allow any digit sequence on each side, but will check numeric bounds after parsing.
    string s = inf.readLine("[0-9]+:[0-9]+", "line");

    // Split by colon
    size_t pos = s.find(':');
    // There must be exactly one colon (regex guarantees at least one, but check split logic)
    ensuref(pos != string::npos, "Line does not contain ':' separator");
    string a_str = s.substr(0, pos);
    string b_str = s.substr(pos + 1);

    // Neither part should be empty (regex ensures at least one digit)
    ensuref(!a_str.empty(), "Missing n before ':'");
    ensuref(!b_str.empty(), "Missing m after ':'");

    // Parse and check numeric ranges
    // Use long long to be safe during conversion
    long long n = 0, m = 0;
    // Convert first part
    {
        // Leading zeros allowed; stoll handles big numbers but we check bounds
        try {
            n = stoll(a_str);
        } catch (...) {
            ensuref(false, "Failed to parse n as integer");
        }
    }
    // Convert second part
    {
        try {
            m = stoll(b_str);
        } catch (...) {
            ensuref(false, "Failed to parse m as integer");
        }
    }

    // Check constraints: 1 ≤ n, m ≤ 100,000,000
    ensuref(1 <= n && n <= 100000000LL,
            "n = %lld is out of bounds [1,100000000]", n);
    ensuref(1 <= m && m <= 100000000LL,
            "m = %lld is out of bounds [1,100000000]", m);

    // Consume EOF
    inf.readEof();
    return 0;
}
