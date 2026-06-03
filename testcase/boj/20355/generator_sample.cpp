#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int mode = rnd.next(0, 5);
    string w;

    if (mode == 0) {
        w.assign(rnd.next(1, 100), rnd.any(alphabet));
    } else if (mode == 1) {
        int distinct = rnd.next(2, 8);
        string letters = alphabet;
        shuffle(letters.begin(), letters.end());
        letters.resize(distinct);

        int len = rnd.next(distinct, min(100, distinct * 8));
        for (int i = 0; i < len; ++i) {
            w += rnd.any(letters);
        }
    } else if (mode == 2) {
        string letters = alphabet;
        shuffle(letters.begin(), letters.end());
        letters.resize(rnd.next(20, 25));
        shuffle(letters.begin(), letters.end());

        int len = rnd.next((int)letters.size(), 100);
        w = letters;
        while ((int)w.size() < len) {
            w += rnd.any(letters);
        }
    } else if (mode == 3) {
        int repeats = rnd.next(1, 3);
        for (int r = 0; r < repeats; ++r) {
            w += alphabet;
        }
        w.resize(rnd.next(26, min(100, (int)w.size())));
    } else if (mode == 4) {
        int len = rnd.next(1, 100);
        char start = rnd.any(alphabet);
        int step = rnd.next(1, 25);
        for (int i = 0; i < len; ++i) {
            w += char('a' + (start - 'a' + i * step) % 26);
        }
    } else {
        int blocks = rnd.next(1, 10);
        for (int b = 0; b < blocks; ++b) {
            char c = rnd.any(alphabet);
            w.append(rnd.next(1, 10), c);
        }
        if ((int)w.size() > 100) {
            w.resize(100);
        }
    }

    println(w);
    return 0;
}
