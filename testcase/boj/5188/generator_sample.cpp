#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomWord(int len, const string& alphabet) {
    string s;
    for (int i = 0; i < len; ++i) s += rnd.any(alphabet);
    return s;
}

string mutateOneChar(string s, const string& alphabet) {
    int pos = rnd.next(0, static_cast<int>(s.size()) - 1);
    char replacement = rnd.any(alphabet);
    if (alphabet.size() > 1) {
        while (replacement == s[pos]) replacement = rnd.any(alphabet);
    }
    s[pos] = replacement;
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string smallAlpha = "abc";
    const string mixedAlpha = "aAbBcC";
    const int k = rnd.next(3, 8);
    println(k);

    for (int tc = 0; tc < k; ++tc) {
        int mode = rnd.next(0, 4);
        vector<string> pieces;
        string z;

        if (mode == 0) {
            int segmentCount = rnd.next(2, 8);
            for (int i = 0; i < segmentCount; ++i) {
                string part = randomWord(rnd.next(1, 4), smallAlpha);
                pieces.push_back(part);
                z += part;
            }
            int extra = rnd.next(1, 8);
            for (int i = 0; i < extra; ++i) {
                pieces.push_back(randomWord(rnd.next(1, 5), smallAlpha));
            }
        } else if (mode == 1) {
            z = randomWord(rnd.next(5, 16), "ab");
            for (int len = 1; len <= min(4, static_cast<int>(z.size())); ++len) {
                for (int start = 0; start + len <= static_cast<int>(z.size()); ++start) {
                    if (rnd.next(0, 2) == 0) pieces.push_back(z.substr(start, len));
                }
            }
            if (pieces.empty()) pieces.push_back(z.substr(0, 1));
        } else if (mode == 2) {
            int segmentCount = rnd.next(2, 6);
            for (int i = 0; i < segmentCount; ++i) {
                string part = randomWord(rnd.next(1, 3), mixedAlpha);
                pieces.push_back(part);
                z += part;
            }
            pieces.push_back(mutateOneChar(z.substr(0, rnd.next(1, min(5, static_cast<int>(z.size())))), mixedAlpha));
            pieces.push_back(randomWord(rnd.next(1, 4), mixedAlpha));
        } else if (mode == 3) {
            z = randomWord(rnd.next(4, 14), "ab") + "Z";
            int options = rnd.next(2, 8);
            for (int i = 0; i < options; ++i) {
                pieces.push_back(randomWord(rnd.next(1, 4), "ab"));
            }
        } else {
            int len = rnd.next(6, 18);
            z = string(len, rnd.any(string("ab")));
            pieces.push_back(string(1, z[0]));
            pieces.push_back(string(2, z[0]));
            pieces.push_back(string(3, z[0]));
            if (rnd.next(0, 1) == 1) pieces.push_back(string(1, z[0] == 'a' ? 'b' : 'a'));
        }

        sort(pieces.begin(), pieces.end());
        pieces.erase(unique(pieces.begin(), pieces.end()), pieces.end());
        shuffle(pieces.begin(), pieces.end());
        if (pieces.size() > 20) pieces.resize(20);

        println(static_cast<int>(pieces.size()));
        println(z);
        for (const string& piece : pieces) println(piece);
    }

    return 0;
}
