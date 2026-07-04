#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 30);
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string s;

    if (mode == 0) {
        char c = rnd.next('a', 'z');
        s.assign(n, c);
    } else if (mode == 1) {
        char a = rnd.next('a', 'z');
        char b = rnd.next('a', 'z');
        while (b == a) b = rnd.next('a', 'z');
        for (int i = 0; i < n; ++i) s += (i % 2 == 0 ? a : b);
    } else if (mode == 2) {
        int blockCount = rnd.next(1, min(6, n));
        vector<char> letters;
        for (int i = 0; i < blockCount; ++i) letters.push_back(rnd.next('a', 'z'));
        while ((int)s.size() < n) {
            int len = rnd.next(1, min(5, n - (int)s.size()));
            s.append(len, rnd.any(letters));
        }
    } else if (mode == 3) {
        int distinct = rnd.next(1, 26);
        shuffle(alphabet.begin(), alphabet.end());
        alphabet.resize(distinct);
        for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    } else {
        n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) s += rnd.next('a', 'z');
    }

    int q = rnd.next(1, 40);
    println(s);
    println(q);

    for (int i = 0; i < q; ++i) {
        char alpha;
        if (rnd.next(0, 1) == 0) {
            alpha = rnd.any(s);
        } else {
            alpha = rnd.next('a', 'z');
        }

        int l = 0;
        int r = n - 1;
        int queryMode = rnd.next(0, 5);
        if (queryMode == 0) {
            l = r = rnd.next(0, n - 1);
        } else if (queryMode == 1) {
            r = rnd.next(0, n - 1);
        } else if (queryMode == 2) {
            l = rnd.next(0, n - 1);
        } else if (queryMode == 3) {
            l = rnd.next(0, n - 1);
            r = rnd.next(l, n - 1);
        } else if (queryMode == 4 && n >= 2) {
            int mid = rnd.next(0, n - 2);
            l = mid;
            r = mid + 1;
        }

        println(alpha, l, r);
    }

    return 0;
}
