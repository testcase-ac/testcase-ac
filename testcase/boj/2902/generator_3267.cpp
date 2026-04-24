#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of segments, 1 to 5, mixed distribution
    int segs;
    if (rnd.next() < 0.5)
        segs = rnd.next(1, 5);
    else
        segs = rnd.wnext(5, 1) + 1;  // max of two samples from [0,4] +1 => [1,5]

    // Build the hyphen-separated name
    string s;
    for (int i = 0; i < segs; i++) {
        if (i > 0) s += '-';

        // Hyper-parameter: segment length, sometimes small, sometimes larger
        int len;
        if (rnd.next() < 0.5)
            len = rnd.next(1, 3);
        else
            len = rnd.next(2, 10);

        // First letter uppercase
        s += char(rnd.next('A', 'Z'));
        // Following letters lowercase
        for (int j = 1; j < len; j++)
            s += char(rnd.next('a', 'z'));
    }

    // Output the generated input
    println(s);
    return 0;
}
