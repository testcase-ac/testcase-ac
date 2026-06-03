#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    shuffle(alphabet.begin(), alphabet.end());

    int tLen = rnd.next(1, 8);
    string t = alphabet.substr(0, tLen);

    string s;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int copies = rnd.next(1, 8);
        for (int i = 0; i < copies; ++i) s += t;
    } else if (mode == 1) {
        int copies = rnd.next(1, 8);
        string block = t;
        reverse(block.begin(), block.end());
        for (int i = 0; i < copies; ++i) s += block;
    } else if (mode == 2) {
        int copies = rnd.next(1, 6);
        for (char ch : t) {
            int count = rnd.next(1, copies + 2);
            s.append(count, ch);
        }
    } else if (mode == 3) {
        int copies = rnd.next(1, 5);
        string noise = alphabet.substr(tLen);
        if (noise.empty()) noise = t;
        for (int i = 0; i < copies; ++i) {
            for (char ch : t) {
                if (rnd.next(0, 1)) s += rnd.any(noise);
                s += ch;
            }
            if (rnd.next(0, 1)) s += rnd.any(noise);
        }
    } else if (mode == 4) {
        int length = rnd.next(tLen, min(80, max(tLen, tLen * 10)));
        for (int i = 0; i < length; ++i) s += rnd.any(t);
    } else {
        int length = rnd.next(tLen, 80);
        for (int i = 0; i < length; ++i) s += rnd.any(alphabet);
        vector<int> positions(length);
        for (int i = 0; i < length; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        sort(positions.begin(), positions.begin() + tLen);
        for (int i = 0; i < tLen; ++i) s[positions[i]] = t[i];
    }

    if (s.empty()) s = t;

    println(s);
    println(t);

    return 0;
}
