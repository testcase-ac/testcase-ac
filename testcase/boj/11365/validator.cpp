#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cnt = 0;
    while (true) {
        // Read next line (up to 500 characters, excluding newline)
        string s = inf.readLine("[^]{0,500}", "cipher");
        cnt++;
        // If it's the terminator, stop reading ciphers
        if (s == "END") {
            cnt--;  // "END" is not a cipher
            break;
        }
        // No further per-line constraints
    }
    // At most 100000 cipher lines
    ensuref(cnt <= 100000, "Number of cipher lines %d exceeds limit %d", cnt, 100000);

    inf.readEof();
    return 0;
}
