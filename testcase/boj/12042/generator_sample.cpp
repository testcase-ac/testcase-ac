#include "testlib.h"
#include <string>

using namespace std;

string makeWord(int mode, int len) {
    string word;
    word.reserve(len);

    if (mode == 0) {
        char c = char('a' + rnd.next(26));
        return string(len, c);
    }

    if (mode == 1) {
        char a = char('a' + rnd.next(26));
        char b = char('a' + rnd.next(26));
        while (b == a) b = char('a' + rnd.next(26));
        for (int i = 0; i < len; ++i) word.push_back(i % 2 == 0 ? a : b);
        return word;
    }

    if (mode == 2) {
        int alphabetSize = rnd.next(2, 5);
        for (int i = 0; i < len; ++i) word.push_back(char('a' + rnd.next(alphabetSize)));
        return word;
    }

    if (mode == 3) {
        char base = char('a' + rnd.next(26));
        word.assign(len, base);
        int changes = rnd.next(1, len);
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(len);
            char c = char('a' + rnd.next(26));
            while (c == base) c = char('a' + rnd.next(26));
            word[pos] = c;
        }
        return word;
    }

    for (int i = 0; i < len; ++i) word.push_back(char('a' + rnd.next(26)));
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 100);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = rnd.next(5);
        int len = rnd.next(1, 5);

        if (caseIndex < 5) {
            len = caseIndex + 1;
            mode = caseIndex;
        }

        println(makeWord(mode, len));
    }

    return 0;
}
