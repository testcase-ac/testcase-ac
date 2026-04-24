#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of the string
    int L = rnd.next(1, 10);
    // Alphabet size from 'a' to 'a'+alphSize-1
    int alphSize = rnd.next(1, 5);

    // Utility to pick a random character
    auto randChar = [&]() {
        return char('a' + rnd.next(0, alphSize - 1));
    };

    string s(L, 'a');
    double mode = rnd.next();  // hyper-parameter to choose generation mode

    if (L == 1 || mode < 0.3) {
        // Mode 1: completely random string
        for (int i = 0; i < L; ++i)
            s[i] = randChar();
    } else if (mode < 0.65) {
        // Mode 2: a short pattern repeated to fill length L
        int patLen = rnd.next(1, L / 2);
        string pat(patLen, 'a');
        for (int i = 0; i < patLen; ++i)
            pat[i] = randChar();
        int times = (L + patLen - 1) / patLen;
        string tmp;
        for (int i = 0; i < times; ++i)
            tmp += pat;
        s = tmp.substr(0, L);
    } else {
        // Mode 3: random string with one substring copied elsewhere
        for (int i = 0; i < L; ++i)
            s[i] = randChar();
        if (L >= 2) {
            int pl = rnd.next(1, L / 2);
            int i1 = rnd.next(0, L - pl);
            int i2 = rnd.next(0, L - pl);
            while (i2 == i1)
                i2 = rnd.next(0, L - pl);
            for (int j = 0; j < pl; ++j)
                s[i2 + j] = s[i1 + j];
        }
    }

    // Output
    println(L);
    printf("%s\n", s.c_str());
    return 0;
}
