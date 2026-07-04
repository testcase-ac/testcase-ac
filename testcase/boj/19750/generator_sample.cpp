#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string suffixFor(int index, int total) {
    return "(" + to_string(index) + "/" + to_string(total) + ")";
}

string randomWord(int mode) {
    static const vector<string> plain = {
        "Winter", "twinter", "snow", "sledge", "message", "chain", "short",
        "long", "word", "tiny", "reformat", "coming", "people", "write"
    };
    static const vector<string> punct = {
        "Hello!", "wait,", "end.", "sylla-", "A?", "x:y", "v2", "42",
        "mix;case", "name1", "quote'", "dash-", "a+b", "x<y"
    };

    if (mode == 0) {
        return rnd.any(plain);
    }
    if (mode == 1) {
        return rnd.any(punct);
    }

    int len = rnd.next(1, 12);
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?.,-:;'";
    string word;
    for (int i = 0; i < len; ++i) {
        word += rnd.any(alphabet);
    }
    return word;
}

string randomContent(int maxLen, int mode) {
    string content = randomWord(mode);
    while (true) {
        string next = randomWord(mode);
        if ((int)content.size() + 1 + (int)next.size() > maxLen) {
            break;
        }
        if (rnd.next(0, 99) < 35 && (int)content.size() >= maxLen / 2) {
            break;
        }
        content += ' ';
        content += next;
    }
    return content;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 4);
    int n;
    if (shape == 0) {
        n = 1;
    } else if (shape == 1) {
        n = rnd.next(2, 5);
    } else if (shape == 2) {
        n = rnd.next(6, 15);
    } else {
        n = rnd.next(16, 35);
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        string suffix = suffixFor(i, n);
        int maxContentLen = 140 - (int)suffix.size() - 1;
        int mode = rnd.next(0, 2);

        if (shape == 0) {
            maxContentLen = rnd.next(1, min(maxContentLen, 20));
        } else if (shape == 3 && rnd.next(0, 99) < 40) {
            maxContentLen = rnd.next(max(1, maxContentLen - 20), maxContentLen);
        } else {
            maxContentLen = rnd.next(1, min(maxContentLen, 80));
        }

        println(randomContent(maxContentLen, mode) + " " + suffix);
    }

    return 0;
}
