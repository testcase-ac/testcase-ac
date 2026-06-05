#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string shuffledPrefix(int k) {
    vector<char> letters;
    for (int i = 0; i < 26; ++i) {
        letters.push_back(char('a' + i));
    }
    shuffle(letters.begin(), letters.end());

    string result;
    for (int i = 0; i < k; ++i) {
        result += letters[i];
    }
    return result;
}

void shuffleString(string& s) {
    vector<char> chars(s.begin(), s.end());
    shuffle(chars.begin(), chars.end());
    s.assign(chars.begin(), chars.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string s;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        int pairs = rnd.next(1, 35);
        int alphabet = rnd.next(1, min(26, pairs));
        string letters = shuffledPrefix(alphabet);
        for (int i = 0; i < pairs; ++i) {
            char c = rnd.any(letters);
            s += c;
            s += c;
        }
    } else if (mode == 1) {
        int alphabet = rnd.next(1, 26);
        string letters = shuffledPrefix(alphabet);
        vector<int> counts(alphabet, 1);
        int extraPairs = rnd.next(0, (70 - alphabet) / 2);
        for (int i = 0; i < extraPairs; ++i) {
            counts[rnd.next(0, alphabet - 1)] += 2;
        }
        for (int i = 0; i < alphabet; ++i) {
            s.append(counts[i], letters[i]);
        }
    } else if (mode == 2) {
        int evenLetters = rnd.next(1, 8);
        int oddLetters = rnd.next(1, 8);
        string letters = shuffledPrefix(evenLetters + oddLetters);
        vector<int> counts(evenLetters + oddLetters, 0);
        for (int i = 0; i < evenLetters; ++i) {
            counts[i] = 2;
        }
        for (int i = 0; i < oddLetters; ++i) {
            counts[evenLetters + i] = 1;
        }
        int baseLength = 2 * evenLetters + oddLetters;
        int extraPairs = rnd.next(0, (70 - baseLength) / 2);
        for (int i = 0; i < extraPairs; ++i) {
            counts[rnd.next(0, int(counts.size()) - 1)] += 2;
        }
        for (int i = 0; i < int(counts.size()); ++i) {
            s.append(counts[i], letters[i]);
        }
    } else if (mode == 3) {
        int len = rnd.any(vector<int>{1, 2, 3, 69, 70});
        int alphabet = rnd.next(1, min(26, len));
        string letters = shuffledPrefix(alphabet);
        for (int i = 0; i < len; ++i) {
            s += rnd.any(letters);
        }
    } else if (mode == 4) {
        int alphabet = rnd.next(20, 26);
        string letters = shuffledPrefix(alphabet);
        for (char c : letters) {
            s += c;
        }
        int extraPairs = rnd.next(0, (70 - int(s.size())) / 2);
        for (int i = 0; i < extraPairs; ++i) {
            char c = rnd.any(letters);
            s += c;
            s += c;
        }
    } else if (mode == 5) {
        char c = char('a' + rnd.next(0, 25));
        int len = rnd.next(1, 70);
        s.assign(len, c);
    } else {
        int len = rnd.next(4, 30);
        int alphabet = rnd.next(2, min(10, len));
        string letters = shuffledPrefix(alphabet);
        for (int i = 0; i < len; ++i) {
            s += rnd.any(letters);
        }
    }

    shuffleString(s);
    println(s);
    return 0;
}
