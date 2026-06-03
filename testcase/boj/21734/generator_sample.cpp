#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int len = rnd.next(1, 10);
    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        char c = char('a' + rnd.next(26));
        s.assign(len, c);
    } else if (mode == 1) {
        string letters = "az";
        for (int i = 0; i < len; ++i) s += letters[rnd.next(2)];
    } else if (mode == 2) {
        int alphabetSize = rnd.next(1, 26);
        for (int i = 0; i < len; ++i) s += char('a' + rnd.next(alphabetSize));
    } else if (mode == 3) {
        char start = char('a' + rnd.next(26));
        for (int i = 0; i < len; ++i) s += char('a' + (start - 'a' + i) % 26);
    } else {
        for (int i = 0; i < len; ++i) s += char('a' + rnd.next(26));
    }

    println(s);
    return 0;
}
