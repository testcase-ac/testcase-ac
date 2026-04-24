#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide test type
    vector<string> types = {"none", "happy", "sad", "unsure"};
    string t = rnd.any(types);
    int h = 0, s = 0;
    if (t == "none") {
        h = 0; s = 0;
    } else if (t == "happy") {
        s = rnd.next(0, 3);
        h = s + rnd.next(1, 4);
    } else if (t == "sad") {
        h = rnd.next(0, 3);
        s = h + rnd.next(1, 4);
    } else { // unsure
        h = rnd.next(1, 4);
        s = h;
    }

    // Build emoticon list and shuffle
    vector<string> emos;
    for (int i = 0; i < h; i++) emos.push_back(":-)");
    for (int i = 0; i < s; i++) emos.push_back(":-(");
    shuffle(emos.begin(), emos.end());

    int cnt = emos.size();
    // Determine filler lengths
    int maxF = 5;
    vector<int> lens(cnt + 1);
    if (cnt == 0) {
        // at least one char if no emoticons
        lens[0] = rnd.next(1, min(10, 255));
    } else {
        for (int i = 0; i <= cnt; i++)
            lens[i] = rnd.next(0, maxF);
    }

    // Alphabet for filler (avoid colon, hyphen, parentheses)
    string alph = "abcdefghijklmnopqrstuvwxyz"
                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  "0123456789 .,!?";

    // Build the final string
    string res;
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < lens[i]; j++)
            res += rnd.any(alph);
        res += emos[i];
    }
    for (int j = 0; j < lens[cnt]; j++)
        res += rnd.any(alph);

    // Truncate or fix empty
    if (res.empty()) res = "a";
    if (res.size() > 255) res = res.substr(0, 255);

    // Output
    printf("%s\n", res.c_str());
    return 0;
}
