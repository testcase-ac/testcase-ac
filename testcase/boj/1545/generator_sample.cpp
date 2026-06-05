#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(45, 50);
    } else {
        n = rnd.next(2, 30);
    }

    string s;
    if (mode == 2) {
        char heavy = char('a' + rnd.next(0, 25));
        int count = rnd.next((n + 1) / 2 + 1, n);
        s.append(count, heavy);
        for (int i = count; i < n; ++i) {
            char c = char('a' + rnd.next(0, 25));
            if (c == heavy) c = char('a' + (c - 'a' + 1) % 26);
            s.push_back(c);
        }
    } else if (mode == 3) {
        int alphabet = rnd.next(2, min(8, n));
        vector<int> counts(alphabet, 0);
        for (int i = 0; i < n; ++i) {
            int c = rnd.wnext(alphabet, -2);
            if (counts[c] < (n + 1) / 2) {
                ++counts[c];
            } else {
                --i;
            }
        }
        for (int i = 0; i < alphabet; ++i) s.append(counts[i], char('a' + i));
    } else if (mode == 4) {
        int pairs = n / 2;
        for (int i = 0; i < pairs; ++i) {
            char c = char('a' + rnd.next(0, min(25, pairs + 2)));
            s.push_back(c);
            s.push_back(c);
        }
        if (n % 2 == 1) s.push_back(char('a' + rnd.next(0, 25)));
    } else if (mode == 5) {
        int alphabet = rnd.next(1, min(26, n));
        for (int i = 0; i < n; ++i) s.push_back(char('a' + i % alphabet));
    } else {
        int alphabet = rnd.next(1, min(26, n));
        for (int i = 0; i < n; ++i) s.push_back(char('a' + rnd.next(0, alphabet - 1)));
    }

    shuffle(s.begin(), s.end());
    println(s);
    return 0;
}
