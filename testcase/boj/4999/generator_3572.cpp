#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: maximum a's for Jae-hwan
    int maxA1 = rnd.next(0, 10);
    // Use weighted distribution to get diverse count1
    int t = rnd.next(-2, 2);
    int count1 = rnd.wnext(maxA1 + 1, t);

    // Decide if it's a "go" case (count1 >= count2) or "no" case (count1 < count2)
    bool ok = rnd.next(0, 1) == 1;
    if (count1 == maxA1) {
        // If count1 is at its cap, we can't have count2 > count1
        ok = true;
    }

    int count2;
    if (ok) {
        // Ensure count2 <= count1
        count2 = rnd.next(0, count1);
    } else {
        // Ensure count2 > count1, with a small upper bound for hand-checking
        int maxB = rnd.next(count1 + 1, maxA1 + 5);
        count2 = rnd.next(count1 + 1, maxB);
    }

    // Build the strings: 'a'*count + 'h'
    string s1(count1, 'a');
    s1 += 'h';
    string s2(count2, 'a');
    s2 += 'h';

    // Output
    println(s1);
    println(s2);

    return 0;
}
