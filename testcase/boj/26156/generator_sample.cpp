#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(4, 60);
    string s;

    if (mode == 0) {
        string letters = "ABDEFGHIJLMNPQSTUVWXYZ";
        for (int i = 0; i < n; ++i) {
            s += rnd.any(letters);
        }
    } else if (mode == 1) {
        string letters = "ROCK";
        for (int i = 0; i < n; ++i) {
            s += rnd.any(letters);
        }
    } else if (mode == 2) {
        string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < n; ++i) {
            s += rnd.any(letters);
        }
    } else if (mode == 3) {
        vector<int> cuts = {0, n};
        for (int i = 0; i < 3; ++i) {
            cuts.push_back(rnd.next(1, n - 1));
        }
        sort(cuts.begin(), cuts.end());
        string letters = "ROCK";
        for (int i = 0; i < 4; ++i) {
            s += string(cuts[i + 1] - cuts[i], letters[i]);
        }
    } else if (mode == 4) {
        int repeats = rnd.next(1, max(1, n / 4));
        s.reserve(n);
        for (int i = 0; i < repeats; ++i) {
            s += "ROCK";
        }
        string noise = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        while ((int)s.size() < n) {
            s += rnd.any(noise);
        }
        shuffle(s.begin(), s.end());
    } else if (mode == 5) {
        vector<char> parts;
        string base = "ROCK";
        for (char c : base) {
            int take = rnd.next(1, 12);
            for (int i = 0; i < take; ++i) {
                parts.push_back(c);
            }
        }
        shuffle(parts.begin(), parts.end());
        for (char c : parts) {
            s += c;
        }
        n = (int)s.size();
    } else {
        n = rnd.next(40, 200);
        string letters = "AROCKN";
        for (int i = 0; i < n; ++i) {
            s += rnd.any(letters);
        }
    }

    println(n);
    println(s);
    return 0;
}
