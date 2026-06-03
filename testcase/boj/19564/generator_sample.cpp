#include "testlib.h"

#include <string>

using namespace std;

string increasingRun(int len, char start, int maxStep) {
    string s;
    s.push_back(start);
    for (int i = 1; i < len; ++i) {
        int remaining = 'z' - s.back();
        if (remaining == 0) break;
        int step = rnd.next(1, min(maxStep, remaining));
        s.push_back(char(s.back() + step));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int len = rnd.next(1, 26);
        char start = char('a' + rnd.next(0, 26 - len));
        for (int i = 0; i < len; ++i) s.push_back(char(start + i));
    } else if (mode == 1) {
        int len = rnd.next(1, 30);
        char base = char('a' + rnd.next(26));
        s.assign(len, base);
    } else if (mode == 2) {
        int len = rnd.next(2, 30);
        char cur = char('a' + rnd.next(26));
        for (int i = 0; i < len; ++i) {
            s.push_back(cur);
            cur = char('a' + rnd.next(cur - 'a' + 1));
        }
    } else if (mode == 3) {
        int runs = rnd.next(2, 8);
        for (int i = 0; i < runs; ++i) {
            int len = rnd.next(1, 5);
            char start = char('a' + rnd.next(26));
            s += increasingRun(len, start, rnd.next(1, 4));
        }
    } else if (mode == 4) {
        int len = rnd.next(1, 30);
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < len; ++i) s.push_back(rnd.any(alphabet));
    } else {
        int repeats = rnd.next(1, 4);
        string block = increasingRun(rnd.next(1, 26), 'a', 1);
        for (int i = 0; i < repeats; ++i) s += block;
    }

    println(s);
    return 0;
}
