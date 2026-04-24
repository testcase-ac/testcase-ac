#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: between 1 and 10
    int T = rnd.next(1, 10);

    for (int i = 0; i < T; i++) {
        // Generate a number with 1 to 4 digits, value 1..9999
        int len = rnd.next(1, 4);
        string s;
        // First digit: '1' to '9' (no leading zero)
        s += char('1' + rnd.next(0, 8));
        // Remaining digits: '0' to '9'
        for (int j = 1; j < len; j++) {
            s += char('0' + rnd.next(0, 9));
        }
        println(s);
    }
    // Sentinel
    println(0);

    return 0;
}
