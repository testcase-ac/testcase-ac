#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

bool isPeriodic(const string &s) {
    int n = s.size();
    for (int d = 1; d < n; ++d) {
        if (n % d != 0) continue;
        bool ok = true;
        for (int i = d; i < n; ++i) {
            if (s[i] != s[i - d]) { ok = false; break; }
        }
        if (ok) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of test cases (up to 10)
    int T = rnd.next(1, 10);

    for (int tc = 0; tc < T; ++tc) {
        // decide if this case is a clear repetition or a random string
        bool useRep = rnd.next(0, 1);
        string s;
        if (useRep) {
            // generate a base pattern and repeat it
            int patLen = rnd.next(1, 5);
            int nrep = rnd.next(2, 5);
            string base;
            for (int j = 0; j < patLen; ++j)
                base.push_back(char('a' + rnd.next(0, 25)));
            for (int r = 0; r < nrep; ++r)
                s += base;
        } else {
            // generate a non-periodic string
            int L = rnd.next(1, 10);
            do {
                s.clear();
                for (int j = 0; j < L; ++j)
                    s.push_back(char('a' + rnd.next(0, 25)));
            } while (isPeriodic(s));
        }
        println(s);
    }

    // end marker
    println(".");

    return 0;
}
