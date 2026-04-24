#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Function to generate a test number as string
    auto genNum = [&]() {
        // 20% chance to be "0"
        if (rnd.next(0, 4) == 0) {
            return string("0");
        }
        // Otherwise pick a length between 1 and 20
        int len = rnd.next(1, 20);
        // Pick a digit-pattern type for diversity
        int type = rnd.next(0, 3);
        string s;
        if (type == 0) {
            // Uniform random digits, nonzero first digit
            s.resize(len);
            s[0] = char('1' + rnd.next(0, 8));
            for (int i = 1; i < len; i++) {
                s[i] = char('0' + rnd.next(0, 9));
            }
        } else if (type == 1) {
            // All same digit (1-9)
            char d = char('1' + rnd.next(0, 8));
            s = string(len, d);
        } else if (type == 2) {
            // One non-zero leading digit, rest zeros
            s = string(len, '0');
            s[0] = char('1' + rnd.next(0, 8));
        } else {
            // Repeating sequence "123456789"
            const string base = "123456789";
            s.resize(len);
            for (int i = 0; i < len; i++) {
                s[i] = base[i % base.size()];
            }
        }
        return s;
    };

    // Generate A and B
    string A = genNum();
    string B = genNum();
    // Output
    println(A, B);

    return 0;
}
