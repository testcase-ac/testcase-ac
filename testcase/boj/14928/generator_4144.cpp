#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: length of the big number
    int L = rnd.next(1, 20);

    // Four types of test patterns
    int type = rnd.next(0, 3);
    string s;
    const string base = "20000303";

    switch (type) {
        case 0:
            // Random digits, no leading zero
            s += char('1' + rnd.next(0, 8));
            for (int i = 1; i < L; i++)
                s += char('0' + rnd.next(0, 9));
            break;
        case 1:
            // Random digits, allow leading zeros
            for (int i = 0; i < L; i++)
                s += char('0' + rnd.next(0, 9));
            break;
        case 2:
            // All zeros
            s = string(L, '0');
            break;
        case 3:
            // Repeating the pattern "20000303"
            while ((int)s.size() < L)
                s += base;
            s.resize(L);
            break;
    }

    // Output the big integer
    println(s);
    return 0;
}
