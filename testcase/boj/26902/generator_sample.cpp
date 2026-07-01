#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomDigits(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += char('0' + rnd.next(0, 9));
    }
    return s;
}

string randomSegment(bool allowLeadingZero) {
    if (rnd.next(0, 4) == 0) return "0";

    int value = rnd.next(1, 255);
    string s = to_string(value);
    if (allowLeadingZero && s.size() < 3 && rnd.next(0, 2) == 0) {
        s = string(rnd.next(1, 3 - int(s.size())), '0') + s;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        s = string(rnd.next(4, 12), '0');
    } else if (mode == 1) {
        int len = rnd.next(4, 12);
        s = randomDigits(len);
        int pos = rnd.next(0, len - 2);
        s[pos] = '0';
        if (s[pos + 1] == '0') s[pos + 1] = char('1' + rnd.next(0, 8));
    } else if (mode == 2) {
        vector<string> parts;
        for (int i = 0; i < 4; ++i) parts.push_back(randomSegment(false));
        for (const string& part : parts) s += part;
    } else if (mode == 3) {
        vector<string> traps = {"256", "257", "299", "999"};
        s = rnd.any(traps);
        while (int(s.size()) < 4) s += char('0' + rnd.next(0, 9));
        while (int(s.size()) < 12 && rnd.next(0, 1) == 0) s += char('0' + rnd.next(0, 9));
        shuffle(s.begin(), s.end());
    } else if (mode == 4) {
        vector<string> parts;
        for (int i = 0; i < 4; ++i) parts.push_back(randomSegment(true));
        for (const string& part : parts) s += part;
        if (s.size() > 12) s.resize(12);
    } else {
        s = randomDigits(rnd.next(4, 12));
    }

    println(s);
    return 0;
}
