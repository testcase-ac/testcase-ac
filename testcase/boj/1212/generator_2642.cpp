#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate a random length for the octal number (1 to 10 digits)
    int L = rnd.next(1, 10);

    string s;
    s.reserve(L);
    for (int i = 0; i < L; i++) {
        if (i == 0 && L > 1) {
            // Leading digit: 1-7 to avoid unnecessary leading zeros
            s.push_back(char('1' + rnd.next(0, 6)));
        } else {
            // Subsequent digits: 0-7
            s.push_back(char('0' + rnd.next(0, 7)));
        }
    }

    // Occasionally produce exactly "0" for edge case
    if (rnd.next(0, 9) == 0) {
        s = "0";
    }

    // Output the octal string
    println(s);

    return 0;
}
