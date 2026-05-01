#include "testlib.h"
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Some clearly edge case: all zeros
    if (rnd.next(0, 9) == 0) {
        println("00:00:00");
        return 0;
    }

    vector<string> invalids = {"13", "00", "60", "99"};
    vector<string> parts;
    for (int i = 0; i < 3; i++) {
        int mode = rnd.next(0, 4);
        string s;
        if (mode == 0) {
            // valid hour
            int x = rnd.next(1, 12);
            char buf[3];
            sprintf(buf, "%02d", x);
            s = buf;
        } else if (mode == 1) {
            // valid minute/second
            int x = rnd.next(0, 59);
            char buf[3];
            sprintf(buf, "%02d", x);
            s = buf;
        } else if (mode == 2) {
            // common invalid tokens
            s = rnd.any(invalids);
        } else {
            // fully random two-digit
            int x = rnd.next(0, 99);
            char buf[3];
            sprintf(buf, "%02d", x);
            s = buf;
        }
        parts.push_back(s);
    }

    // Output time string
    println(parts[0] + ":" + parts[1] + ":" + parts[2]);
    return 0;
}
