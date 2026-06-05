#include "testlib.h"

#include <string>

using namespace std;

string censor(string s, const string& t) {
    string result;
    for (char c : s) {
        result.push_back(c);
        if (result.size() >= t.size() &&
            result.compare(result.size() - t.size(), t.size(), t) == 0) {
            result.resize(result.size() - t.size());
        }
    }
    return result;
}

string randomString(int length, const string& alphabet) {
    string s;
    for (int i = 0; i < length; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "abcde";

    while (true) {
        int mode = rnd.next(0, 4);
        string t;
        string s;

        if (mode == 0) {
            int lenT = rnd.next(1, 8);
            t = randomString(lenT, "z");
            s = randomString(rnd.next(lenT, 30), alphabet);
        } else if (mode == 1) {
            int lenT = rnd.next(1, 6);
            t = randomString(lenT, alphabet);
            int pieces = rnd.next(2, 8);
            for (int i = 0; i < pieces; ++i) {
                if (rnd.next(0, 2) == 0) {
                    s += t;
                }
                s += randomString(rnd.next(1, 4), alphabet);
            }
        } else if (mode == 2) {
            char c = char('a' + rnd.next(0, 3));
            int lenT = rnd.next(1, 8);
            t.assign(lenT, c);
            s.assign(rnd.next(lenT, 30), c);
            s.push_back(char('e' + rnd.next(0, 1)));
        } else if (mode == 3) {
            string mid = randomString(rnd.next(1, 3), alphabet);
            char left = rnd.any(string("abc"));
            char right = rnd.any(string("de"));
            t = string(1, left) + mid + string(1, right);
            s = string(1, left) + mid + t + string(1, right);
            s += randomString(rnd.next(1, 6), alphabet);
        } else {
            int lenT = rnd.next(2, 8);
            t = randomString(lenT, alphabet);
            s = randomString(rnd.next(lenT, 30), alphabet);
        }

        if (t.size() <= s.size() && !censor(s, t).empty()) {
            println(s);
            println(t);
            return 0;
        }
    }
}
