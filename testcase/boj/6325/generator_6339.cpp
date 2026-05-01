#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of program parts
    int T = rnd.next(1, 5);
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    vector<char> letters(alpha.begin(), alpha.end());

    vector<vector<pair<char,char>>> parts;
    for (int ti = 0; ti < T; ti++) {
        int type = rnd.next(0, 4);
        vector<pair<char,char>> part;
        if (type == 0) {
            // Chain from 'a'
            int L = rnd.next(1, min(8, 25));
            vector<char> pool(letters.begin() + 1, letters.end()); // b..z
            shuffle(pool.begin(), pool.end());
            pool.resize(L);
            char prev = 'a';
            for (char v : pool) {
                part.emplace_back(v, prev);
                prev = v;
            }
        } else if (type == 1) {
            // Cycle including 'a'
            int k = rnd.next(2, min(6, 25));
            vector<char> pool = letters;
            shuffle(pool.begin(), pool.end());
            pool.resize(k);
            bool hasA = false;
            for (char c : pool) if (c == 'a') hasA = true;
            if (!hasA) {
                pool[0] = 'a';
                shuffle(pool.begin(), pool.end());
            }
            for (int i = 0; i < k; i++) {
                char src = pool[i];
                char dst = pool[(i+1)%k];
                part.emplace_back(dst, src);
            }
        } else if (type == 2) {
            // Pure random assignments
            int n = rnd.next(1, 12);
            for (int i = 0; i < n; i++) {
                char lhs = rnd.any(letters);
                char rhs = rnd.any(letters);
                part.emplace_back(lhs, rhs);
            }
        } else if (type == 3) {
            // Self-heavy assignments
            int n = rnd.next(1, 10);
            for (int i = 0; i < n; i++) {
                if (rnd.next(0, 99) < 70) {
                    char c = rnd.any(letters);
                    part.emplace_back(c, c);
                } else {
                    char lhs = rnd.any(letters);
                    char rhs = rnd.any(letters);
                    part.emplace_back(lhs, rhs);
                }
            }
        } else {
            // Sink: assign everything from 'z'
            int n = rnd.next(1, 8);
            vector<char> pool(letters.begin(), letters.end()-1); // a..y
            for (int i = 0; i < n; i++) {
                char lhs = rnd.any(pool);
                part.emplace_back(lhs, 'z');
            }
        }
        parts.push_back(part);
    }

    // Output all parts and terminating 0
    for (auto &part : parts) {
        println((int)part.size());
        for (auto &pr : part) {
            printf("%c = %c\n", pr.first, pr.second);
        }
    }
    println(0);
    return 0;
}
