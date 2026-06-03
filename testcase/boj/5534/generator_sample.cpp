#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomString(int length) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s.push_back(char('a' + rnd.next(26)));
    }
    return s;
}

string makeName() {
    int length = rnd.next(3, 12);
    string name = randomString(length);

    if (rnd.next(4) == 0) {
        char c = char('a' + rnd.next(26));
        for (char& ch : name) ch = c;
    } else if (rnd.next(3) == 0) {
        string pattern = randomString(rnd.next(2, 4));
        for (int i = 0; i < length; ++i) name[i] = pattern[i % int(pattern.size())];
    }

    return name;
}

string makeMatchingSign(const string& name) {
    int step = rnd.next(1, max(1, 100 / int(name.size())));
    int minLength = 1 + step * (int(name.size()) - 1);
    int length = rnd.next(minLength, min(100, minLength + rnd.next(0, 20)));
    int start = rnd.next(0, length - minLength);
    string sign = randomString(length);

    for (int i = 0; i < int(name.size()); ++i) {
        sign[start + step * i] = name[i];
    }
    return sign;
}

string makeNearMissSign(const string& name) {
    string sign = makeMatchingSign(name);
    vector<int> positions;

    for (int step = 1; step < int(sign.size()); ++step) {
        for (int start = 0; start + step * (int(name.size()) - 1) < int(sign.size()); ++start) {
            bool matches = true;
            for (int i = 0; i < int(name.size()); ++i) {
                if (sign[start + step * i] != name[i]) {
                    matches = false;
                    break;
                }
            }
            if (matches) positions.push_back(start + step * rnd.next(int(name.size())));
        }
    }

    if (!positions.empty()) {
        int pos = rnd.any(positions);
        char replacement = char('a' + rnd.next(26));
        while (replacement == sign[pos]) replacement = char('a' + rnd.next(26));
        sign[pos] = replacement;
    }

    return sign;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string name = makeName();
    int n = rnd.next(1, 20);
    vector<string> signs;
    signs.reserve(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(100);
        if (mode < 25) {
            signs.push_back(makeMatchingSign(name));
        } else if (mode < 40) {
            signs.push_back(name);
        } else if (mode < 60) {
            signs.push_back(makeNearMissSign(name));
        } else if (mode < 75) {
            signs.push_back(randomString(rnd.next(1, int(name.size()) - 1)));
        } else {
            signs.push_back(randomString(rnd.next(1, 30)));
        }
    }

    println(n);
    println(name);
    for (const string& sign : signs) println(sign);

    return 0;
}
