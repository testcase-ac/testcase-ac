#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

char letterWithCase(int value, bool upper) {
    value %= 26;
    return static_cast<char>((upper ? 'A' : 'a') + value);
}

void appendAlternatingChar(string& s, int value) {
    bool upper = s.empty() ? (rnd.next(2) == 0)
                           : !isupper(static_cast<unsigned char>(s.back()));
    s.push_back(letterWithCase(value, upper));
}

void appendPair(string& s, int first, int second) {
    appendAlternatingChar(s, first);
    appendAlternatingChar(s, second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int pairs = rnd.next(1, 14);
    int alphabet = rnd.next(1, 8);
    string s;

    if (mode == 0) {
        int a = rnd.next(alphabet);
        int b = rnd.next(alphabet);
        for (int i = 0; i < pairs; ++i) {
            appendPair(s, a, b);
        }
    } else if (mode == 1) {
        int cur = rnd.next(alphabet);
        for (int i = 0; i < pairs; ++i) {
            appendPair(s, cur, (cur + 1 + rnd.next(alphabet)) % 26);
            cur = (cur + 1) % alphabet;
        }
    } else if (mode == 2) {
        for (int i = 0; i < pairs; ++i) {
            int a = i % alphabet;
            int b = (i * 3 + rnd.next(alphabet)) % alphabet;
            appendPair(s, a, b);
        }
    } else if (mode == 3) {
        vector<int> letters;
        for (int i = 0; i < alphabet; ++i) {
            letters.push_back(i);
        }
        shuffle(letters.begin(), letters.end());
        for (int i = 0; i < pairs; ++i) {
            appendPair(s, letters[i % alphabet], letters[(i + 1) % alphabet]);
        }
    } else {
        int length = rnd.next(2, 29);
        for (int i = 0; i < length; ++i) {
            appendAlternatingChar(s, rnd.next(alphabet));
        }
    }

    println(s);
    return 0;
}
