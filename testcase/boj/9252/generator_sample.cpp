#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomString(int n, const string& alphabet) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += alphabet[rnd.next((int)alphabet.size())];
    }
    return s;
}

string repeatedPattern(int n, const string& pattern) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += pattern[i % pattern.size()];
    }
    return s;
}

string withNoise(const string& core, const string& noiseAlphabet) {
    string s;
    for (char c : core) {
        if (rnd.next(2)) {
            s += randomString(rnd.next(1, 3), noiseAlphabet);
        }
        s += c;
    }
    if (rnd.next(2)) {
        s += randomString(rnd.next(1, 4), noiseAlphabet);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    string a, b;

    if (mode == 0) {
        int n = rnd.next(1, 24);
        int m = rnd.next(1, 24);
        a = randomString(n, "ABC");
        b = randomString(m, "XYZ");
    } else if (mode == 1) {
        int n = rnd.next(1, 28);
        int m = rnd.next(1, 28);
        a = repeatedPattern(n, rnd.any(vector<string>{"AB", "ABC", "AAB"}));
        b = repeatedPattern(m, rnd.any(vector<string>{"BA", "BCA", "ABA"}));
    } else if (mode == 2) {
        int coreLen = rnd.next(1, 12);
        string core = randomString(coreLen, "ABCDE");
        a = withNoise(core, "FGH");
        b = withNoise(core, "IJK");
    } else if (mode == 3) {
        int n = rnd.next(4, 26);
        a = randomString(n, "ABCDE");
        b = a;
        shuffle(b.begin(), b.end());
        if (rnd.next(2)) {
            a += randomString(rnd.next(1, 5), "VW");
        }
        if (rnd.next(2)) {
            b = randomString(rnd.next(1, 5), "YZ") + b;
        }
    } else {
        int n = rnd.next(1, 30);
        int m = rnd.next(1, 30);
        char maxChar = char('A' + rnd.next(0, 7));
        string alphabet;
        for (char c = 'A'; c <= maxChar; ++c) {
            alphabet += c;
        }
        a = randomString(n, alphabet);
        b = randomString(m, alphabet);
    }

    println(a);
    println(b);
    return 0;
}
