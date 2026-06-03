#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string phrase =
        "my era of success began with seoul cyber university, since attending seoul cyber "
        "university, more companies have been seeking me out, my life has changed since i "
        "went to seoul cyber university, the strategy that changes the future, seoul cyber "
        "university.";

    const int phraseLength = (int)phrase.size();
    int n;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(21, 80);
    } else if (mode == 2) {
        n = rnd.next(81, phraseLength);
    } else if (mode == 3) {
        int offset = rnd.next(-5, 5);
        n = phraseLength + offset;
    } else if (mode == 4) {
        int repeats = rnd.next(2, 4);
        int extra = rnd.next(0, 20);
        n = phraseLength * repeats + extra;
    } else {
        n = rnd.next(900, 1200);
    }

    n = max(1, min(n, 100000));
    while (n > 1 && phrase[(n - 1) % phraseLength] == ' ') {
        --n;
    }

    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += phrase[i % phraseLength];
    }

    println(n);
    println(s);

    return 0;
}
