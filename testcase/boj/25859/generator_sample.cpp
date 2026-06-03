#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 8);
        char c = char('a' + rnd.next(26));
        s.assign(n, c);
    } else if (mode == 1) {
        int kinds = rnd.next(2, 10);
        int repeats = rnd.next(1, 5);
        for (int i = 0; i < kinds; ++i) {
            char c = char('a' + i);
            s.append(repeats, c);
        }
    } else if (mode == 2) {
        int kinds = rnd.next(2, 8);
        vector<char> letters;
        for (int i = 0; i < kinds; ++i) letters.push_back(char('a' + i));
        shuffle(letters.begin(), letters.end());

        int high = rnd.next(3, 14);
        for (int i = 0; i < kinds; ++i) {
            int count = max(1, high - i - rnd.next(0, 2));
            s.append(count, letters[i]);
        }
    } else if (mode == 3) {
        int n = rnd.next(15, 35);
        int maxLetter = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) s.push_back(char('a' + rnd.next(maxLetter + 1)));
    } else if (mode == 4) {
        int n = rnd.next(55, 70);
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < n; ++i) s.push_back(alphabet[i % int(alphabet.size())]);
    } else {
        int n = rnd.next(25, 70);
        char dominant = char('a' + rnd.next(26));
        char secondary = char('a' + rnd.next(26));
        while (secondary == dominant) secondary = char('a' + rnd.next(26));

        int dominantCount = rnd.next(n / 2, n - 1);
        s.append(dominantCount, dominant);
        for (int i = dominantCount; i < n; ++i) {
            if (rnd.next(3) == 0) {
                s.push_back(secondary);
            } else {
                s.push_back(char('a' + rnd.next(26)));
            }
        }
    }

    shuffle(s.begin(), s.end());
    println(s);
    return 0;
}
