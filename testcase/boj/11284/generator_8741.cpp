#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string encodeUtf8(int cp) {
    string s;
    if (cp <= 0x7F) {
        s.push_back(char(cp));
    } else if (cp <= 0x7FF) {
        s.push_back(char(0xC0 | (cp >> 6)));
        s.push_back(char(0x80 | (cp & 0x3F)));
    } else if (cp <= 0xFFFF) {
        s.push_back(char(0xE0 | (cp >> 12)));
        s.push_back(char(0x80 | ((cp >> 6) & 0x3F)));
        s.push_back(char(0x80 | (cp & 0x3F)));
    } else {
        s.push_back(char(0xF0 | (cp >> 18)));
        s.push_back(char(0x80 | ((cp >> 12) & 0x3F)));
        s.push_back(char(0x80 | ((cp >> 6) & 0x3F)));
        s.push_back(char(0x80 | (cp & 0x3F)));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int HANGUL_BASE = 0xAC00;
    const int HANGUL_LAST = 0xD7A3;

    // Jongseong index sets (excluding 0 which means no final consonant)
    vector<int> simpleT = {
        1, 2, 4, 7, 8, 16, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27
    };
    vector<int> complexT = {
        3, 5, 6, 9, 10, 11, 12, 13, 14, 15, 18
    };

    int mode = rnd.next(1, 10);
    int cp;

    if (mode == 1) {
        // Very first syllable: 가
        cp = HANGUL_BASE;
    } else if (mode == 2) {
        // Very last syllable: 힣
        cp = HANGUL_LAST;
    } else if (mode <= 4) {
        // No jongseong
        int L = rnd.next(0, 18);
        int V = rnd.next(0, 20);
        int T = 0;
        cp = HANGUL_BASE + ((L * 21 + V) * 28 + T);
    } else if (mode <= 6) {
        // Simple jongseong
        int L = rnd.next(0, 18);
        int V = rnd.next(0, 20);
        int T = rnd.any(simpleT);
        cp = HANGUL_BASE + ((L * 21 + V) * 28 + T);
    } else if (mode <= 8) {
        // Complex jongseong (consonant clusters)
        int L = rnd.next(0, 18);
        int V = rnd.next(0, 20);
        int T = rnd.any(complexT);
        cp = HANGUL_BASE + ((L * 21 + V) * 28 + T);
    } else {
        // Fully random Hangul syllable in U+AC00..U+D7A3
        cp = rnd.next(HANGUL_BASE, HANGUL_LAST);
    }

    string s = encodeUtf8(cp);
    println(s);

    return 0;
}
