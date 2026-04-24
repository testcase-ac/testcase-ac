#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // String length hyper-parameter
    int N = rnd.next(1, 10);
    // Alphabet maximum character
    int maxc = rnd.next(0, 25); // 'a' to 'a'+maxc

    string s(N, 'a');
    // Decide whether to introduce a small periodic pattern
    if (rnd.next() < 0.3) {
        int pl = rnd.next(1, N);
        string pat(pl, 'a');
        for (int i = 0; i < pl; i++)
            pat[i] = char('a' + rnd.next(0, maxc));
        // Repeat the pattern
        for (int i = 0; i < N; i++)
            s[i] = pat[i % pl];
        // Add some random noise
        for (int i = 0; i < N; i++)
            if (rnd.next() < 0.1)
                s[i] = char('a' + rnd.next(0, maxc));
    } else {
        // Fully random string
        for (int i = 0; i < N; i++)
            s[i] = char('a' + rnd.next(0, maxc));
    }

    // Output the generated string
    printf("%s\n", s.c_str());
    return 0;
}
