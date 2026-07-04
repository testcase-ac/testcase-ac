#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

char randomUpperExceptHYU() {
    static const string letters = "ABCDEFGIJKLMNOPQRSTVWXZ";
    return rnd.any(letters);
}

char randomLower() {
    return char('a' + rnd.next(26));
}

char randomHYU() {
    static const string letters = "HYU";
    return rnd.any(letters);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 40);
    int d = rnd.next(1, 100);
    int m = rnd.next(1, 100);
    string s;

    if (mode == 0) {
        // Mostly removable letters in short runs.
        while ((int)s.size() < n) {
            int run = min(rnd.next(1, 6), n - (int)s.size());
            char c = rnd.next(2) == 0 ? randomLower() : randomUpperExceptHYU();
            s.append(run, c);
            if ((int)s.size() < n && rnd.next(100) < 55) s.push_back(randomHYU());
        }
        s.resize(n);
    } else if (mode == 1) {
        // HYU-heavy string with scattered deletion candidates.
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(100);
            if (pick < 75) s.push_back(randomHYU());
            else if (pick < 88) s.push_back(randomLower());
            else s.push_back(randomUpperExceptHYU());
        }
    } else if (mode == 2) {
        // Skewed counts of H, Y, and U.
        char dominant = randomHYU();
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(100);
            if (pick < 65) s.push_back(dominant);
            else if (pick < 85) s.push_back(randomHYU());
            else s.push_back(rnd.next(2) == 0 ? randomLower() : randomUpperExceptHYU());
        }
    } else if (mode == 3) {
        // Alternating useful and removable blocks.
        while ((int)s.size() < n) {
            int block = min(rnd.next(1, 5), n - (int)s.size());
            if (rnd.next(2) == 0) {
                for (int i = 0; i < block; ++i) s.push_back(randomHYU());
            } else {
                char c = rnd.next(2) == 0 ? randomLower() : randomUpperExceptHYU();
                s.append(block, c);
            }
        }
    } else if (mode == 4) {
        // No useful letters.
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next(2) == 0 ? randomLower() : randomUpperExceptHYU());
        }
    } else {
        // Very small edge cases, including single-character strings.
        n = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(4);
            if (pick == 0) s.push_back('H');
            else if (pick == 1) s.push_back('Y');
            else if (pick == 2) s.push_back('U');
            else s.push_back(randomLower());
        }
        d = rnd.any(vector<int>{1, 2, 99, 100});
        m = rnd.any(vector<int>{1, 2, 99, 100});
    }

    println(n);
    println(s);
    println(d, m);
    return 0;
}
