#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomString(int len, const string& alphabet, bool allowSpaces) {
    string s;
    bool previousSpace = false;
    for (int i = 0; i < len; ++i) {
        string choices = alphabet;
        if (allowSpaces && i > 0 && i + 1 < len && !previousSpace) {
            choices += ' ';
        }

        char c = rnd.any(choices);
        s += c;
        previousSpace = c == ' ';
    }
    return s;
}

string uriLikeString(int len) {
    const vector<string> chunks = {
        "http://", "https://", "ftp://", "mailto:", "icpc", "baylor", "edu",
        "pub", "linux", "readme", ".txt", "/", ".", "_", "-", "127", "0",
        "1", "?", "=", "&"};

    string s;
    while ((int)s.size() < len) {
        if (!s.empty() && rnd.next(5) == 0 && (int)s.size() + 1 < len) {
            s += ' ';
        }
        const string& chunk = rnd.any(chunks);
        int remaining = len - (int)s.size();
        s += chunk.substr(0, remaining);
    }

    while (!s.empty() && s.back() == ' ') {
        s.back() = 'x';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string plain = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-/:?=&@";
    const string reserved = "!$%()*";
    const string mixed = plain + reserved;

    int lineCount = rnd.next(3, 12);
    vector<string> lines;
    lines.reserve(lineCount);

    for (int i = 0; i < lineCount; ++i) {
        int mode = rnd.next(0, 5);
        int len = rnd.next(1, 30);
        if (mode == 5) {
            len = rnd.any(vector<int>{1, 2, 3, 78, 79});
        }

        if (mode == 0) {
            lines.push_back(randomString(len, plain, false));
        } else if (mode == 1) {
            lines.push_back(randomString(len, mixed, true));
        } else if (mode == 2) {
            lines.push_back(randomString(len, reserved, false));
        } else if (mode == 3) {
            lines.push_back(uriLikeString(len));
        } else if (mode == 4) {
            string s = randomString(len, plain, true);
            int positions = rnd.next(1, max(1, len / 3));
            for (int j = 0; j < positions; ++j) {
                int pos = rnd.next(0, len - 1);
                if (s[pos] != ' ') {
                    s[pos] = rnd.any(reserved);
                }
            }
            lines.push_back(s);
        } else {
            lines.push_back(randomString(len, mixed, true));
        }
    }

    shuffle(lines.begin(), lines.end());
    for (const string& line : lines) {
        println(line);
    }
    println("#");

    return 0;
}
