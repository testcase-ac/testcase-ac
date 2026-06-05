#include "testlib.h"

#include <cstdio>
#include <string>
#include <vector>
using namespace std;

bool canEncode(char c) {
    return c == 'a' || c == 'c' || c == 'i' || c == 'j' || c == 'n' || c == 'o' ||
           c == 't' || c == 'v' || c == 'w';
}

string encodeChar(char c) {
    if (c == 'a') return "@";
    if (c == 'c') return "[";
    if (c == 'i') return "!";
    if (c == 'j') return ";";
    if (c == 'n') return "^";
    if (c == 'o') return "0";
    if (c == 't') return "7";
    if (c == 'v') return "\\'";
    if (c == 'w') return "\\\\'";
    return string(1, c);
}

string makeWord(int len, int changed) {
    const string plain = "bdefghklmpqrsuxyz";
    const string encodable = "acijnotvw";

    string decoded;
    for (int i = 0; i < len; ++i) {
        if (i < changed) {
            decoded += rnd.any(encodable);
        } else {
            decoded += rnd.next(3) == 0 ? rnd.any(encodable) : rnd.any(plain);
        }
    }

    shuffle(decoded.begin(), decoded.end());

    vector<int> positions;
    for (int i = 0; i < len; ++i) {
        if (canEncode(decoded[i])) positions.push_back(i);
    }
    shuffle(positions.begin(), positions.end());

    vector<bool> encoded(len, false);
    for (int i = 0; i < changed; ++i) {
        encoded[positions[i]] = true;
    }

    string result;
    for (int i = 0; i < len; ++i) {
        if (encoded[i]) {
            result += encodeChar(decoded[i]);
        } else {
            result += decoded[i];
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(6, 24);
    println(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(8);
        int len;
        int changed;

        if (mode == 0) {
            len = 1;
            changed = rnd.next(0, 1);
        } else if (mode == 1) {
            len = rnd.next(2, 12);
            changed = (len - 1) / 2;
        } else if (mode == 2) {
            len = rnd.next(2, 12);
            changed = (len + 1) / 2;
        } else if (mode == 3) {
            len = rnd.next(13, 30);
            changed = rnd.next(0, len / 3);
        } else if (mode == 4) {
            len = rnd.next(13, 30);
            changed = rnd.next((len + 1) / 2, len);
        } else if (mode == 5) {
            len = rnd.next(90, 100);
            changed = rnd.next(0, len / 2);
        } else if (mode == 6) {
            len = rnd.next(90, 100);
            changed = rnd.next((len + 1) / 2, len);
        } else {
            len = rnd.next(3, 20);
            changed = rnd.next(0, len);
        }

        string word = makeWord(len, changed);
        printf("%s\n", word.c_str());
    }

    return 0;
}
