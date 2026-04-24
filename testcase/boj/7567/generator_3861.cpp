#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length between 3 and 10
    int n = rnd.next(3, 10);
    // Probability to continue same direction
    double sameProb = rnd.next(0.0, 1.0);

    string s;
    s.reserve(n);
    // First bowl random
    s.push_back(rnd.any(string("()")));
    // Generate the rest
    for (int i = 1; i < n; i++) {
        if (rnd.next() < sameProb) {
            s.push_back(s[i - 1]);
        } else {
            s.push_back(s[i - 1] == '(' ? ')' : '(');
        }
    }

    // Output the test case
    println(s);

    return 0;
}
