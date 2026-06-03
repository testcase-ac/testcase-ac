#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string randomWord(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string s;
    for (int i = 0; i < len; ++i) {
        char base = rnd.next(0, 1) == 0 ? 'a' : 'A';
        s += char(base + rnd.next(0, 25));
    }
    return s;
}

string randomPhrase() {
    int words = rnd.next(1, 5);
    string s = randomWord(1, 8);
    for (int i = 1; i < words; ++i) {
        s += ' ';
        s += randomWord(1, 8);
    }
    if ((int)s.size() > 50)
        s.resize(50);
    while (!s.empty() && s.back() == ' ')
        s.pop_back();
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> promises = {
        "Never gonna give you up",
        "Never gonna let you down",
        "Never gonna run around and desert you",
        "Never gonna make you cry",
        "Never gonna say goodbye",
        "Never gonna tell a lie and hurt you",
        "Never gonna stop"
    };
    vector<string> changed = {
        "Never gonna give you down",
        "Never gonna Let you down",
        "Never gonna run around  and desert you",
        "Never gonna make you smile",
        "Never gonna say hello",
        "Never gonna tell two lies and hurt you",
        "Never gonna Stop",
        "A",
        "Changed Promise"
    };

    int mode = rnd.next(0, 3);
    int n = mode == 0 ? rnd.next(1, 7) : rnd.next(1, 20);
    vector<string> lines;

    if (mode == 0) {
        for (int i = 0; i < n; ++i)
            lines.push_back(rnd.any(promises));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i)
            lines.push_back(rnd.next(0, 2) == 0 ? rnd.any(promises) : rnd.any(changed));
    } else if (mode == 2) {
        int badPos = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i)
            lines.push_back(i == badPos ? rnd.any(changed) : rnd.any(promises));
    } else {
        for (int i = 0; i < n; ++i)
            lines.push_back(rnd.next(0, 3) == 0 ? rnd.any(promises) : randomPhrase());
    }

    println(n);
    for (const string& line : lines)
        println(line);

    return 0;
}
