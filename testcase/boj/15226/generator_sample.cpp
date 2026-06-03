#include "testlib.h"

#include <string>
using namespace std;

string randomDigits(int len) {
    string s;
    s.reserve(len);
    s.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < len; ++i) {
        s.push_back(char('0' + rnd.next(10)));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    string h0;

    if (mode == 0) {
        h0 = to_string(rnd.next(1, 60));
    } else if (mode == 1) {
        long long base = rnd.next(1, 250);
        h0 = to_string(base * 4 + rnd.next(4));
    } else if (mode == 2) {
        int len = rnd.next(2, 30);
        h0 = randomDigits(len);
    } else if (mode == 3) {
        int len = rnd.next(31, 120);
        h0 = randomDigits(len);
    } else if (mode == 4) {
        int exp = rnd.next(1, 1000);
        h0 = "1" + string(exp, '0');
    } else {
        int len = rnd.next(900, 1000);
        h0 = randomDigits(len);
    }

    println(h0);
    return 0;
}
