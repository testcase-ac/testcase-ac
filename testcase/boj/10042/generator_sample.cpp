#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    string s;
    const string people = "JOI";

    if (mode == 0) {
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) s += rnd.any(people);
    } else if (mode == 1) {
        n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) s += rnd.any(people);
    } else if (mode == 2) {
        n = rnd.next(2, 100);
        char c = rnd.any(people);
        s.assign(n, c);
    } else if (mode == 3) {
        n = rnd.next(2, 90);
        string pattern;
        int patternLen = rnd.next(2, 3);
        for (int i = 0; i < patternLen; ++i) pattern += people[i];
        shuffle(pattern.begin(), pattern.end());
        for (int i = 0; i < n; ++i) s += pattern[i % patternLen];
    } else if (mode == 4) {
        n = rnd.next(10, 100);
        char common = rnd.any(people);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 70) {
                s += common;
            } else {
                s += rnd.any(people);
            }
        }
    } else if (mode == 5) {
        n = rnd.next(12, 100);
        while ((int)s.size() < n) {
            char c = rnd.any(people);
            int run = rnd.next(1, 12);
            while (run-- > 0 && (int)s.size() < n) s += c;
        }
    } else {
        n = rnd.any(vector<int>{2, 999, 1000});
        for (int i = 0; i < n; ++i) s += rnd.any(people);
    }

    println(n);
    println(s);

    return 0;
}
