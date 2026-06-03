#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

char randomLower(int alphabetSize) {
    return char('a' + rnd.next(0, alphabetSize - 1));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    string s;

    if (mode == 0) {
        s.assign(n, randomLower(rnd.next(1, 4)));
    } else if (mode == 1) {
        int alphabetSize = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) s += char('a' + (i % alphabetSize));
    } else if (mode == 2) {
        s.resize(n);
        int alphabetSize = rnd.next(1, 6);
        for (int i = 0; i < (n + 1) / 2; ++i) {
            char c = randomLower(alphabetSize);
            s[i] = c;
            s[n - 1 - i] = c;
        }
    } else if (mode == 3) {
        s.resize(n);
        int alphabetSize = rnd.next(2, 8);
        for (int i = 0; i < (n + 1) / 2; ++i) {
            char c = randomLower(alphabetSize);
            s[i] = c;
            s[n - 1 - i] = c;
        }
        int changes = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < changes; ++i) s[rnd.next(0, n - 1)] = randomLower(alphabetSize);
    } else if (mode == 4) {
        vector<char> letters;
        int alphabetSize = rnd.next(2, 6);
        for (int i = 0; i < alphabetSize; ++i) letters.push_back(char('a' + i));
        shuffle(letters.begin(), letters.end());
        while ((int)s.size() < n) {
            char c = letters[rnd.next(0, alphabetSize - 1)];
            int run = rnd.next(1, min(6, n - (int)s.size()));
            s.append(run, c);
        }
    } else {
        int alphabetSize = rnd.next(1, 26);
        for (int i = 0; i < n; ++i) s += randomLower(alphabetSize);
    }

    println(s);
    return 0;
}
