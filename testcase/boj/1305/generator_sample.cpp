#include "testlib.h"
#include <string>

using namespace std;

string randomString(int length, const string& alphabet) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int length = rnd.next(1, 30);
        s.assign(length, rnd.any(string("abc")));
    } else if (mode == 1) {
        int periodLength = rnd.next(1, 10);
        string period = randomString(periodLength, "abc");
        int repeats = rnd.next(1, 6);
        s.reserve(periodLength * repeats);
        for (int i = 0; i < repeats; ++i) {
            s += period;
        }
    } else if (mode == 2) {
        int periodLength = rnd.next(2, 10);
        string period = randomString(periodLength, "abcd");
        int repeats = rnd.next(2, 5);
        s.reserve(periodLength * repeats);
        for (int i = 0; i < repeats; ++i) {
            s += period;
        }
        s[rnd.next(0, (int)s.size() - 1)] = rnd.any(string("xyz"));
    } else if (mode == 3) {
        int coreLength = rnd.next(1, 10);
        string core = randomString(coreLength, "abc");
        int tailLength = rnd.next(0, coreLength);
        s = core + randomString(rnd.next(0, 8), "abc") + core.substr(0, tailLength);
    } else if (mode == 4) {
        int length = rnd.next(2, 30);
        s = randomString(length, "abcdefghijklmnopqrstuvwxyz");
    } else {
        int aCount = rnd.next(1, 15);
        int bCount = rnd.next(1, 15);
        s = string(aCount, 'a') + string(bCount, 'b') + string(rnd.next(0, 8), 'a');
    }

    println((int)s.size());
    println(s);
    return 0;
}
