#include "testlib.h"

#include <string>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long randomValue(int mode) {
    if (mode == 0) return rnd.next(1LL, 30LL);
    if (mode == 1) return rnd.next(1LL, 1000LL);
    if (mode == 2) return LIMIT - rnd.next(0LL, 1000LL);
    return rnd.next(1LL, LIMIT);
}

string randomC(int mode) {
    if (mode == 0) {
        return to_string(rnd.next(1, 12));
    }

    int len;
    if (mode == 1) {
        len = rnd.next(1, 20);
    } else if (mode == 2) {
        len = rnd.next(50, 120);
    } else {
        len = rnd.next(900, 1000);
    }

    string c;
    c += char('1' + rnd.next(9));
    for (int i = 1; i < len; ++i) {
        if (mode == 3 && rnd.next(0, 4) == 0) {
            c += rnd.any(string("09"));
        } else {
            c += char('0' + rnd.next(10));
        }
    }
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int case_index = 0; case_index < t; ++case_index) {
        int mode = rnd.next(0, 3);
        long long a = randomValue(mode);
        long long b = randomValue(rnd.next(0, 3));
        int digitIndex = rnd.next(1, 6);
        string c = randomC(mode);

        if (case_index == 0 && rnd.next(2) == 0) {
            a = 1;
            b = rnd.next(1LL, 10LL);
            c = "1";
        } else if (case_index == 1 && t > 1 && rnd.next(2) == 0) {
            a = LIMIT;
            b = LIMIT;
            digitIndex = 6;
            c = randomC(3);
        }

        println(a, b, digitIndex, c);
    }

    return 0;
}
