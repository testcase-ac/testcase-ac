#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string takeChars(const string& source, int count) {
    vector<char> chars(source.begin(), source.end());
    shuffle(chars.begin(), chars.end());
    return string(chars.begin(), chars.begin() + count);
}

string makeString(string base, const string& pool, int targetLength) {
    vector<char> extra;
    for (char c : pool) {
        if (base.find(c) == string::npos) {
            extra.push_back(c);
        }
    }
    shuffle(extra.begin(), extra.end());
    while (static_cast<int>(base.size()) < targetLength && !extra.empty()) {
        base.push_back(extra.back());
        extra.pop_back();
    }
    return base;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int mode = rnd.next(0, 4);
    int minLength = rnd.next(1, 12);
    int maxLength = rnd.next(minLength, 17);

    vector<string> strings(3);

    if (mode == 0) {
        int commonLength = rnd.next(1, minLength);
        string common = takeChars(alphabet, commonLength);
        for (int i = 0; i < 3; ++i) {
            strings[i] = makeString(common, alphabet, rnd.next(commonLength, maxLength));
            shuffle(strings[i].begin(), strings[i].end());
        }
    } else if (mode == 1) {
        int sharedLength = rnd.next(1, minLength);
        string shared = takeChars(alphabet, sharedLength);
        strings[0] = makeString(shared, alphabet, rnd.next(sharedLength, maxLength));
        strings[1] = makeString(shared, alphabet, rnd.next(sharedLength, maxLength));
        strings[2] = makeString("", alphabet, rnd.next(minLength, maxLength));
        shuffle(strings[0].begin(), strings[0].end());
        shuffle(strings[1].begin(), strings[1].end());
        shuffle(strings[2].begin(), strings[2].end());
    } else if (mode == 2) {
        string base = takeChars(alphabet, maxLength);
        strings[0] = base.substr(0, rnd.next(minLength, maxLength));
        strings[1] = strings[0];
        reverse(strings[1].begin(), strings[1].end());
        strings[2] = makeString(base.substr(0, rnd.next(1, minLength)), alphabet,
                                rnd.next(minLength, maxLength));
    } else if (mode == 3) {
        vector<char> chars(alphabet.begin(), alphabet.end());
        shuffle(chars.begin(), chars.end());
        int cursor = 0;
        for (int i = 0; i < 3; ++i) {
            int length = rnd.next(1, 8);
            strings[i] = string(chars.begin() + cursor, chars.begin() + cursor + length);
            cursor += length;
        }
    } else {
        int length = rnd.next(1, 17);
        string one = takeChars(alphabet, length);
        strings[0] = one;
        strings[1] = one;
        strings[2] = one;
        minLength = length;
    }

    minLength = min({static_cast<int>(strings[0].size()), static_cast<int>(strings[1].size()),
                     static_cast<int>(strings[2].size())});
    int k;
    if (rnd.next(0, 2) == 0) {
        k = rnd.next(1, minLength);
    } else {
        k = rnd.any(vector<int>{1, max(1, minLength / 2), minLength});
    }

    println(strings[0]);
    println(strings[1]);
    println(strings[2]);
    println(k);

    return 0;
}
