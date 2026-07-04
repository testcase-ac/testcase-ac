#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomAllowedChar(const vector<bool>& forbidden) {
    vector<char> allowed;
    for (int c = 0; c < 26; ++c) {
        if (!forbidden[c]) {
            allowed.push_back(char('a' + c));
        }
    }
    return rnd.any(allowed);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int k;
    if (mode == 0) {
        n = 1;
        k = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        k = rnd.next(1, 24);
    } else if (mode == 2) {
        n = rnd.next(6, 18);
        k = rnd.next(1, 12);
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        k = rnd.next(20, 45);
    } else {
        n = rnd.next(20, 35);
        k = rnd.next(1, 8);
    }

    vector<string> basis(k, string(n, 'a'));
    string a(n, 'a');
    string b(n, 'a');

    for (int col = 0; col < n; ++col) {
        vector<char> pool;
        if (mode == 0) {
            pool = {'a', 'b', 'c', 'd', 'e'};
        } else if (mode == 1) {
            pool = {'x', 'y', 'z'};
        } else if (mode == 3) {
            for (char ch = 'a'; ch <= 'y'; ++ch) {
                pool.push_back(ch);
            }
        } else {
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                pool.push_back(ch);
            }
        }

        shuffle(pool.begin(), pool.end());
        int distinctForbidden = rnd.next(1, min<int>(25, pool.size()));
        if (mode == 1) {
            distinctForbidden = rnd.next(1, min<int>(2, pool.size()));
        }

        vector<bool> forbidden(26, false);
        vector<char> chosen(pool.begin(), pool.begin() + distinctForbidden);
        for (char ch : chosen) {
            forbidden[ch - 'a'] = true;
        }

        for (int row = 0; row < k; ++row) {
            if (mode == 3 && row < (int)chosen.size()) {
                basis[row][col] = chosen[row];
            } else {
                basis[row][col] = rnd.any(chosen);
            }
        }

        a[col] = randomAllowedChar(forbidden);
        b[col] = randomAllowedChar(forbidden);
    }

    println(n, k);
    for (const string& s : basis) {
        println(s);
    }
    println(a);
    println(b);

    return 0;
}
