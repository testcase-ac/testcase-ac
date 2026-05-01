#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of words N between 2 and a small value, biased towards small
    int maxN = max(rnd.wnext(10, -1), 2);
    int N = rnd.next(2, maxN);
    // Maximum word length L between 1 and 20, biased towards larger
    int L = rnd.wnext(20, 1) + 1;
    // Threshold to split short/long words
    int hiShort = rnd.next(1, L);
    // Choose an alphabet range [start, end] within 'a' to 'z'
    int start = rnd.next('a', 'z');
    int alphsz = rnd.next(1, 'z' - start + 1);
    int end = start + alphsz - 1;
    // Output N
    println(N);
    // Generate each word
    for (int i = 0; i < N; i++) {
        int len;
        // Half chance to be "short" or "long"
        if (rnd.next(0, 1) == 0)
            len = rnd.next(1, hiShort);
        else
            len = rnd.next(hiShort, L);
        string s;
        s.reserve(len);
        for (int j = 0; j < len; j++) {
            char c = char(rnd.next(start, end));
            s.push_back(c);
        }
        println(s);
    }
    return 0;
}
