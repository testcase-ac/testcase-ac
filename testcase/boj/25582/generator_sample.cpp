#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char pointPartner(char c) {
    if (c == 'p') return 'd';
    if (c == 'd') return 'p';
    if (c == 'b') return 'q';
    if (c == 'q') return 'b';
    if (c == 'u') return 'n';
    if (c == 'n') return 'u';
    return c;
}

char mirrorPartner(char c) {
    if (c == 'p') return 'q';
    if (c == 'q') return 'p';
    if (c == 'b') return 'd';
    if (c == 'd') return 'b';
    return c;
}

string makeSymmetric(const string& pairs, const string& centers, bool point, int len) {
    string left;
    int half = len / 2;
    for (int i = 0; i < half; ++i) {
        left += rnd.any(pairs);
    }

    string s = left;
    if (len % 2 == 1) {
        s += rnd.any(centers);
    }
    for (int i = half - 1; i >= 0; --i) {
        s += point ? pointPartner(left[i]) : mirrorPartner(left[i]);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string all = "abcdefghijklmnopqrstuvwxyz";
    const string noise = "acefghjkrty";
    const string pointPairs = "pdbqunszolx";
    const string mirrorPairs = "pqbdimvwlox";
    const string pointCenters = "szlox";
    const string mirrorCenters = "imvwlox";

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int len = rnd.next(3, 45);
        s = makeSymmetric(mirrorPairs, mirrorCenters, false, len);
    } else if (mode == 1) {
        int len = rnd.next(3, 45);
        s = makeSymmetric(pointPairs, pointCenters, true, len);
    } else if (mode == 2) {
        int n = rnd.next(6, 70);
        s.assign(n, 'a');
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.any(noise);
        }

        int len = rnd.next(3, min(35, n));
        int start = rnd.next(0, n - len);
        bool point = rnd.next(0, 1);
        string core = point
            ? makeSymmetric(pointPairs, pointCenters, true, len)
            : makeSymmetric(mirrorPairs, mirrorCenters, false, len);
        s.replace(start, len, core);
    } else if (mode == 3) {
        int n = rnd.next(3, 80);
        for (int i = 0; i < n; ++i) {
            s += rnd.next(0, 7) == 0 ? rnd.any(all) : rnd.any(noise);
        }
    } else if (mode == 4) {
        int blocks = rnd.next(2, 8);
        for (int i = 0; i < blocks; ++i) {
            bool point = rnd.next(0, 1);
            int len = rnd.next(2, 12);
            if (point) {
                s += makeSymmetric(pointPairs, pointCenters, true, len);
            } else {
                s += makeSymmetric(mirrorPairs, mirrorCenters, false, len);
            }
            if (rnd.next(0, 1)) {
                s += rnd.any(noise);
            }
        }
    } else {
        int n = rnd.next(3, 80);
        string alphabet = rnd.any(vector<string>{"pqbd", "un", "sz", "lox", "imvw"});
        for (int i = 0; i < n; ++i) {
            s += rnd.any(alphabet);
        }
    }

    while ((int)s.size() < 3) {
        s += rnd.any(all);
    }
    println(s);

    return 0;
}
