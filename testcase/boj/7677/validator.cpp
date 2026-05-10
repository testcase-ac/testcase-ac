#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000;
    int case_count = 0;
    while (true) {
        // Read the line as a token (to check for -1 or n)
        string line = inf.readLine("[^]+", "line");
        ensuref(!line.empty(), "Empty line detected at test case %d", case_count + 1);

        // Check for -1 (EOF marker)
        if (line == "-1") {
            break;
        }

        // Check that line is a valid integer (no leading zeros unless "0")
        // and in range 0 <= n <= 1_000_000_000
        // Accept only digits, no leading zeros unless "0"
        ensuref(line.size() <= 10, "Too many digits for n at test case %d: '%s'", case_count + 1, line.c_str());
        for (char c : line) {
            ensuref(c >= '0' && c <= '9', "Non-digit character in n at test case %d: '%s'", case_count + 1, line.c_str());
        }
        if (line.size() > 1) {
            ensuref(line[0] != '0', "Leading zero in n at test case %d: '%s'", case_count + 1, line.c_str());
        }
        // Convert to integer and check range
        long long n = 0;
        for (char c : line) {
            n = n * 10 + (c - '0');
        }
        ensuref(n >= 0 && n <= 1000000000LL, "n out of range at test case %d: %lld", case_count + 1, n);

        ++case_count;
        ensuref(case_count <= MAX_CASES, "Too many test cases: %d (limit %d)", case_count, MAX_CASES);
    }

    // After -1, must be EOF
    inf.readEof();
}
