#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string s(3, 'a');
    int mode = rnd.next(0, 3); // 4 different patterns

    if (mode == 0) {
        // All letters the same, lowercase
        char c = 'a' + rnd.next(0, 25);
        s[0] = s[1] = s[2] = c;
    } else if (mode == 1) {
        // Palindrome: first and last same, middle maybe different
        char a = 'a' + rnd.next(0, 25);
        char b = 'a' + rnd.next(0, 25);
        if (b == a && rnd.next(0, 1) == 0) {
            // sometimes force middle to differ for variety
            b = (a == 'z' ? 'a' : char(a + 1));
        }
        s[0] = s[2] = a;
        s[1] = b;
    } else if (mode == 2) {
        // All distinct lowercase letters (non-palindrome)
        while (true) {
            s[0] = 'a' + rnd.next(0, 25);
            s[1] = 'a' + rnd.next(0, 25);
            s[2] = 'a' + rnd.next(0, 25);
            if (s[0] != s[1] && s[0] != s[2] && s[1] != s[2]) break;
        }
    } else {
        // Digits, any combination
        for (int i = 0; i < 3; ++i)
            s[i] = char('0' + rnd.next(0, 9));
    }

    println(s);
    return 0;
}
