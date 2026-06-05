#include "testlib.h"

#include <climits>
#include <string>

using namespace std;

long long randomK() {
    if (rnd.next(4) == 0) {
        return LLONG_MAX;
    }
    if (rnd.next(3) == 0) {
        return rnd.next(1LL, 1000LL);
    }
    return rnd.next(1LL, LLONG_MAX);
}

char randomDigit(const string& digits) {
    return digits[rnd.next((int)digits.size())];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string ambiguous = "1267";
    const string ordinary = "034589";
    const string allDigits = "0123456789";

    int mode = rnd.next(5);
    int len;
    string password;
    long long k = randomK();

    if (mode == 0) {
        len = rnd.next(1, 30);
        for (int i = 0; i < len; ++i) {
            password += randomDigit(ordinary);
        }
        k = rnd.next(1LL, 1000LL);
    } else if (mode == 1) {
        len = rnd.next(1, 20);
        for (int i = 0; i < len; ++i) {
            password += randomDigit(ambiguous);
        }
        int ambiguousCount = len;
        long long combinations = 1LL << ambiguousCount;
        if (rnd.next(2) == 0) {
            k = rnd.next(1LL, combinations);
        } else {
            k = rnd.next(combinations + 1, combinations + 1000);
        }
    } else if (mode == 2) {
        len = rnd.next(1, 60);
        for (int i = 0; i < len; ++i) {
            if (rnd.next(100) < 45) {
                password += randomDigit(ambiguous);
            } else {
                password += randomDigit(allDigits);
            }
        }
        if (rnd.next(3) == 0) {
            password[0] = '0';
        }
    } else if (mode == 3) {
        len = rnd.next(45, 60);
        for (int i = 0; i < len; ++i) {
            if (rnd.next(100) < 75) {
                password += randomDigit(ambiguous);
            } else {
                password += randomDigit(ordinary);
            }
        }
    } else {
        len = rnd.next(1, 60);
        for (int i = 0; i < len; ++i) {
            password += randomDigit(allDigits);
        }
        password[0] = rnd.next(2) == 0 ? '0' : randomDigit(ambiguous);
        k = rnd.next(1LL, 16LL);
    }

    println(password);
    println(k);
    return 0;
}
