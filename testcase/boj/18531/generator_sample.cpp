#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomWheel(int n, const string& alphabet = "ABC") {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string rotateLeft(const string& s, int shift) {
    int n = static_cast<int>(s.size());
    shift %= n;
    return s.substr(shift) + s.substr(0, shift);
}

char thirdLetter(char a, char b) {
    for (char c : string("ABC")) {
        if (c != a && c != b) {
            return c;
        }
    }
    return 'A';
}

string complementWheel(const string& a, const string& b) {
    string c;
    c.reserve(a.size());
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        c += thirdLetter(a[i], b[i]);
    }
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 30);
    vector<string> wheels(3);

    if (mode == 0) {
        for (string& wheel : wheels) {
            wheel = randomWheel(n);
        }
    } else if (mode == 1) {
        string base = randomWheel(n);
        int bShift = rnd.next(0, n - 1);
        int cShift = rnd.next(0, n - 1);
        wheels[0] = base;
        wheels[1] = rotateLeft(base, bShift);
        wheels[2] = rotateLeft(base, cShift);
    } else if (mode == 2) {
        string a = randomWheel(n);
        string b;
        b.reserve(n);
        for (char ch : a) {
            string choices;
            for (char candidate : string("ABC")) {
                if (candidate != ch) {
                    choices += candidate;
                }
            }
            b += rnd.any(choices);
        }
        string c = complementWheel(a, b);
        wheels[0] = a;
        wheels[1] = rotateLeft(b, rnd.next(0, n - 1));
        wheels[2] = rotateLeft(c, rnd.next(0, n - 1));
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        string pattern = randomWheel(rnd.next(1, min(6, n)));
        for (int i = 0; i < n; ++i) {
            wheels[0] += pattern[i % static_cast<int>(pattern.size())];
        }
        wheels[1] = rotateLeft(wheels[0], rnd.next(0, n - 1));
        wheels[2] = randomWheel(n);
    } else if (mode == 4) {
        n = rnd.next(2, 30);
        vector<char> letters = {'A', 'B', 'C'};
        shuffle(letters.begin(), letters.end());
        for (int i = 0; i < 3; ++i) {
            wheels[i] = string(n, letters[i]);
        }
    } else {
        n = rnd.next(2, 24);
        string a, b, c;
        for (int i = 0; i < n; ++i) {
            char x = static_cast<char>('A' + (i % 3));
            char y = static_cast<char>('A' + ((i + rnd.next(1, 2)) % 3));
            a += x;
            b += y;
            c += thirdLetter(x, y);
        }
        wheels[0] = rotateLeft(a, rnd.next(0, n - 1));
        wheels[1] = rotateLeft(b, rnd.next(0, n - 1));
        wheels[2] = rotateLeft(c, rnd.next(0, n - 1));
    }

    for (const string& wheel : wheels) {
        println(wheel);
    }

    return 0;
}
