#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

// helper to check separator
bool isSep(char c) {
    return !( (c >= 'a' && c <= 'z') ||
              (c >= 'A' && c <= 'Z') ||
              c == '-' );
}

// generate a word of given length, with up to hyCount hyphens if allowHyphens
string makeWord(int length, bool allowHyphens) {
    static const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string w(length, 'a');
    int hyphens = 0;
    if (allowHyphens && length >= 3) {
        // up to 2 hyphens but leave at least one letter on each side
        hyphens = rnd.next(0, min(2, length - 2));
    }
    vector<int> pos(length);
    iota(pos.begin(), pos.end(), 0);
    shuffle(pos.begin(), pos.end());
    for (int i = 0; i < hyphens; i++) {
        w[pos[i]] = '-';
    }
    for (int i = 0; i < length; i++) {
        if (w[i] != '-') {
            w[i] = letters[rnd.next((int)letters.size() - 1)];
        }
    }
    return w;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of tokens (words)
    int T = rnd.wnext(30, -2) + 5;  // more small cases but sometimes larger (5 to ~35)
    // ensure at least one
    T = max(1, T);
    // position of the unique longest word
    int targetPos = rnd.next(0, T - 1);
    // length of longest word: mix of small, medium, large
    int targetLen = rnd.wnext(12, rnd.next(-2, 2)) + 3; // gives 3 to ~15+
    targetLen = min(targetLen, 100);
    // build the special longest word
    string targetWord = makeWord(targetLen, true);
    // generate other words
    vector<string> tokens;
    for (int i = 0; i < T; i++) {
        if (i == targetPos) {
            tokens.push_back(targetWord);
        } else {
            int len = rnd.next(1, max(1, targetLen - 1));
            tokens.push_back(makeWord(len, true));
        }
    }
    // prepare separators
    const string sepChars = " .,!?:;0123456789@#$%&*()[]{}<>/\\|'\"+=_~`";
    vector<string> seps(T);
    for (int i = 0; i < T; i++) {
        int slen = rnd.next(1, 3);
        string s;
        for (int j = 0; j < slen; j++) {
            s += sepChars[rnd.next((int)sepChars.size() - 1)];
        }
        seps[i] = s;
    }
    // build full text (without E-N-D)
    string text;
    for (int i = 0; i < T; i++) {
        text += tokens[i];
        text += seps[i];
    }
    // split into lines without breaking words
    int ptr = 0, N = (int)text.size();
    while (ptr < N) {
        int maxLen = rnd.next(20, 60);
        int end = min(ptr + maxLen, N);
        while (end > ptr && !isSep(text[end - 1])) end--;
        if (end == ptr) {
            end = min(ptr + maxLen, N);
        }
        printf("%s\n", text.substr(ptr, end - ptr).c_str());
        ptr = end;
    }
    // termination marker
    printf("E-N-D\n");
    return 0;
}
