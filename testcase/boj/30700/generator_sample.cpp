#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string koreaPrefix(int len) {
    const string pattern = "KOREA";
    string s;
    for (int i = 0; i < len; ++i) {
        s += pattern[i % (int)pattern.size()];
    }
    return s;
}

void padToMinLength(string& s) {
    const string alphabet = "KOREA";
    while ((int)s.size() < 10) {
        s += rnd.any(alphabet);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "KOREA";
    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int keepLen = rnd.next(1, 25);
        s = koreaPrefix(keepLen);
        int noise = rnd.next(0, 20);
        for (int i = 0; i < noise; ++i) {
            int pos = rnd.next(0, (int)s.size());
            s.insert(s.begin() + pos, rnd.any(alphabet));
        }
    } else if (mode == 1) {
        int runs = rnd.next(2, 8);
        for (int i = 0; i < runs; ++i) {
            char c = alphabet[i % (int)alphabet.size()];
            int count = rnd.next(1, 8);
            s += string(count, c);
        }
    } else if (mode == 2) {
        int len = rnd.next(10, 35);
        string noK = "OREA";
        for (int i = 0; i < len; ++i) {
            s += rnd.any(noK);
        }
    } else if (mode == 3) {
        int target = rnd.next(3, 22);
        s = koreaPrefix(target);
        string distractors = "AAAAAEEEEERRRRROOOOOKKKKK";
        int extra = rnd.next(5, 30);
        for (int i = 0; i < extra; ++i) {
            int pos = rnd.next(0, (int)s.size());
            s.insert(s.begin() + pos, rnd.any(distractors));
        }
    } else if (mode == 4) {
        int blocks = rnd.next(2, 7);
        for (int i = 0; i < blocks; ++i) {
            char c = alphabet[rnd.next(0, 4)];
            int count = rnd.next(1, 10);
            s += string(count, c);
        }
    } else {
        int len = rnd.next(80, 180);
        for (int i = 0; i < len; ++i) {
            double p = rnd.next();
            if (p < 0.35) {
                s += "KOREA"[i % 5];
            } else {
                s += rnd.any(alphabet);
            }
        }
    }

    padToMinLength(s);
    if ((int)s.size() > 1000) {
        s.resize(1000);
    }

    println(s);
    return 0;
}
