#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int randomCost(int mode) {
    if (mode == 0) {
        return rnd.next(1, 5);
    }
    if (mode == 1) {
        return rnd.next(950, 1000);
    }
    if (mode == 2) {
        return rnd.next(1, 1000);
    }
    return rnd.next(0, 3) == 0 ? rnd.next(1, 20) : rnd.next(800, 1000);
}

void appendNoise(string& s, int maxLen) {
    static const string alphabet = "acdfghjklmnopqrtuvwxyz";
    int len = rnd.next(0, maxLen);
    for (int i = 0; i < len; ++i) {
        s += alphabet[rnd.next((int)alphabet.size())];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 25);
        static const string alphabet = "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < n; ++i) {
            s += alphabet[rnd.next((int)alphabet.size())];
        }
    } else if (mode == 1) {
        int copies = rnd.next(1, 5);
        for (int i = 0; i < copies; ++i) {
            appendNoise(s, 3);
            s += "bessie";
        }
        appendNoise(s, 3);
    } else if (mode == 2) {
        int copies = rnd.next(1, 4);
        for (int i = 0; i < copies; ++i) {
            string word = "bessie";
            int extra = rnd.next(1, 4);
            for (int j = 0; j < extra; ++j) {
                word.insert(word.begin() + rnd.next((int)word.size() + 1), rnd.next(0, 1) ? 's' : 'e');
            }
            s += word;
            appendNoise(s, 2);
        }
    } else if (mode == 3) {
        int repeats = rnd.next(2, 6);
        for (int i = 0; i < repeats; ++i) {
            s += rnd.next(0, 1) ? "bes" : "sie";
            appendNoise(s, 2);
        }
    } else if (mode == 4) {
        string block = "bbbbeeessssssiiiieeee";
        shuffle(block.begin(), block.end());
        int len = rnd.next(8, (int)block.size());
        s = block.substr(0, len);
    } else if (mode == 5) {
        int copies = rnd.next(1, 3);
        for (int i = 0; i < copies; ++i) {
            s += "be";
            appendNoise(s, 4);
            s += "ss";
            appendNoise(s, 4);
            s += "ie";
        }
    } else {
        int n = rnd.next(30, 80);
        static const string biased = "bbbeessssiieexyz";
        for (int i = 0; i < n; ++i) {
            s += biased[rnd.next((int)biased.size())];
        }
    }

    int costMode = rnd.next(0, 3);
    vector<int> costs;
    for (int i = 0; i < (int)s.size(); ++i) {
        costs.push_back(randomCost(costMode));
    }

    println(s);
    println(costs);

    return 0;
}
