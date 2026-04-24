#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cnt = 0;
    while (true) {
        // Read a line of length 1 to 255 (we'll check its content or sentinel)
        string s = inf.readLine("[^]{1,255}", "line");
        // Check for sentinel
        if (s == "#") {
            break;
        }
        // Count this test case
        cnt++;
        ensuref(cnt <= 100000,
                "Number of test cases exceeds limit: %d > 100000", cnt);
        // Validate each character in the line
        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            bool ok = false;
            if ((c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                c == ',' ||
                c == '.' ||
                c == '!' ||
                c == '?' ||
                c == ' ')
            {
                ok = true;
            }
            ensuref(ok,
                    "Invalid character '%c' at test case %d, position %d",
                    c, cnt, i + 1);
        }
    }

    // After reading the sentinel, there must be no extra data
    inf.readEof();
    return 0;
}
