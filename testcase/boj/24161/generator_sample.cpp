#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int len = rnd.next(1, 20);
    string s;

    if (mode == 0) {
        s.assign(1, char('A' + rnd.next(0, 25)));
    } else if (mode == 1) {
        s.assign(len, char('A' + rnd.next(0, 25)));
    } else if (mode == 2) {
        for (int i = 0; i < len; ++i) {
            s += char('A' + rnd.next(0, 25));
        }
        sort(s.begin(), s.end());
    } else if (mode == 3) {
        for (int i = 0; i < len; ++i) {
            s += char('A' + rnd.next(0, 25));
        }
        sort(s.rbegin(), s.rend());
    } else if (mode == 4) {
        int alphabet = rnd.next(2, 5);
        for (int i = 0; i < len; ++i) {
            s += char('A' + rnd.next(0, alphabet - 1));
        }
        shuffle(s.begin(), s.end());
    } else if (mode == 5) {
        len = rnd.next(15, 20);
        vector<char> letters;
        int distinct = rnd.next(2, 8);
        for (int i = 0; i < distinct; ++i) {
            letters.push_back(char('A' + rnd.next(0, 25)));
        }
        for (int i = 0; i < len; ++i) {
            s += rnd.any(letters);
        }
        shuffle(s.begin(), s.end());
    } else {
        len = 20;
        for (int i = 0; i < len; ++i) {
            s += char('A' + rnd.next(0, 25));
        }
        shuffle(s.begin(), s.end());
    }

    println(s);
    return 0;
}
