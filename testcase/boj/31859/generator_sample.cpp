#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.any(vector<int>{1, 2, 99, 100, rnd.next(1, 100)});
    int len = rnd.next(1, 20);
    string s;

    if (mode == 0) {
        len = rnd.next(1, 20);
        vector<char> letters;
        for (char c = 'a'; c <= 'z'; ++c) letters.push_back(c);
        shuffle(letters.begin(), letters.end());
        for (int i = 0; i < len; ++i) s += letters[i];
    } else if (mode == 1) {
        len = rnd.next(1, 20);
        char c = rnd.next('a', 'z');
        s.assign(len, c);
    } else if (mode == 2) {
        len = rnd.next(8, 20);
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        int distinct = rnd.next(2, min(8, len));
        shuffle(alphabet.begin(), alphabet.end());
        for (int i = 0; i < distinct; ++i) s += alphabet[i];
        while ((int)s.size() < len) s += s[rnd.next(0, distinct - 1)];
        shuffle(s.begin(), s.end());
    } else if (mode == 3) {
        len = rnd.next(3, 20);
        char first = rnd.next('a', 'z');
        char second = rnd.next('a', 'z');
        while (second == first) second = rnd.next('a', 'z');
        for (int i = 0; i < len; ++i) {
            s += (i % 2 == 0 ? first : second);
        }
    } else if (mode == 4) {
        len = rnd.next(10, 20);
        string block = "smupc";
        while ((int)s.size() < len) {
            char c = block[rnd.next(0, (int)block.size() - 1)];
            s += c;
        }
    } else {
        len = 20;
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        shuffle(alphabet.begin(), alphabet.end());
        int distinct = rnd.next(1, 20);
        for (int i = 0; i < distinct; ++i) s += alphabet[i];
        while ((int)s.size() < len) {
            if (rnd.next(0, 2) == 0) {
                s += s[rnd.next(0, (int)s.size() - 1)];
            } else {
                s += alphabet[rnd.next(0, 25)];
            }
        }
    }

    println(n, s);
    return 0;
}
