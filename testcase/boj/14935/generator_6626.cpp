#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Occasionally output the special case zero
    if (rnd.next(0, 10) == 0) {
        println("0");
        return 0;
    }

    // Choose a group for varied lengths: small, medium, or large
    int grp = rnd.next(0, 2);
    int len;
    if (grp == 0) {
        // small: 1 to 3 digits
        len = rnd.next(1, 3);
    } else if (grp == 1) {
        // medium: 4 to 10 digits
        len = rnd.next(4, 10);
    } else {
        // large: 20 to 100 digits
        len = rnd.next(20, 100);
    }

    // Build the number as a string
    string s;
    s.reserve(len);
    if (len == 1) {
        // Single-digit can be 0-9
        s.push_back(char('0' + rnd.next(0, 9)));
    } else {
        // First digit 1-9 to avoid leading zero
        s.push_back(char('0' + rnd.next(1, 9)));
        for (int i = 1; i < len; i++) {
            s.push_back(char('0' + rnd.next(0, 9)));
        }
    }

    // Output the generated number
    println(s);
    return 0;
}
