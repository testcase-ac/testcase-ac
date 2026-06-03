#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string reversed(string s) {
    reverse(s.begin(), s.end());
    return s;
}

string tail(const string& s) {
    return s.substr(1);
}

string randomBlock(int len, int alphabetSize) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += char('A' + rnd.next(alphabetSize));
    }
    return s;
}

string makeThreeLayer(int len, int form, int alphabetSize) {
    int prefixLen = (len + 2) / 3;
    string p = randomBlock(prefixLen, alphabetSize);
    string rp = reversed(p);

    if (form == 0) return p + rp + p;
    if (form == 1) return p + tail(rp) + p;
    if (form == 2) return p + rp + tail(p);
    return p + tail(rp) + tail(p);
}

int compatibleForm(int len) {
    if (len % 3 == 0) return 0;
    if (len % 3 == 1) return 3;
    return rnd.next(2) == 0 ? 1 : 2;
}

string randomString(int len, int alphabetSize) {
    string s = randomBlock(len, alphabetSize);
    if (alphabetSize > 1) return s;

    int pos = rnd.next(len);
    s[pos] = 'B';
    return s;
}

void perturb(string& s, int alphabetSize) {
    int changes = rnd.next(1, 2);
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next(int(s.size()));
        char c = char('A' + rnd.next(alphabetSize));
        if (c == s[pos]) c = char('A' + (c - 'A' + 1) % max(2, alphabetSize));
        s[pos] = c;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    vector<string> cases;

    cases.push_back(makeThreeLayer(6, compatibleForm(6), 2));
    cases.push_back(makeThreeLayer(30, compatibleForm(30), 4));

    while (int(cases.size()) < t) {
        int mode = rnd.next(5);
        int len = rnd.next(6, 30);
        int alphabetSize = rnd.next(2, 26);

        if (mode <= 2) {
            cases.push_back(makeThreeLayer(len, compatibleForm(len), alphabetSize));
        } else if (mode == 3) {
            string s = makeThreeLayer(len, compatibleForm(len), alphabetSize);
            perturb(s, alphabetSize);
            cases.push_back(s);
        } else {
            cases.push_back(randomString(len, alphabetSize));
        }
    }

    shuffle(cases.begin(), cases.end());
    println(int(cases.size()));
    for (const string& s : cases) {
        println(s);
    }

    return 0;
}
