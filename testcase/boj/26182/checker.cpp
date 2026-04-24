#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input transcript
    int c = inf.readInt();
    int d = inf.readInt();
    if (c > d) // should not happen as per problem statement
        quitf(_fail, "invalid input range: c (%d) > d (%d)", c, d);
    int n = d - c + 1;
    vector<string> transcript(n);
    for (int i = 0; i < n; i++) {
        transcript[i] = inf.readToken();
    }

    // Read contestant's answer: two integers a and b
    int a = ouf.readInt(1, 1000000, "a");
    int b = ouf.readInt(1, 1000000, "b");
    // No extra tokens allowed
    ouf.readEof();

    // Validate that (a, b) generate exactly the given transcript
    for (int i = 0; i < n; i++) {
        int x = c + i;
        bool fizz = (x % a == 0);
        bool buzz = (x % b == 0);
        string expected;
        if (fizz && buzz) expected = "FizzBuzz";
        else if (fizz)     expected = "Fizz";
        else if (buzz)     expected = "Buzz";
        else               expected = to_string(x);

        const string& actual = transcript[i];
        if (actual != expected) {
            quitf(_wa,
                  "at number %d: expected '%s', found '%s'",
                  x, expected.c_str(), actual.c_str());
        }
    }

    // All good
    quitf(_ok, "valid a=%d, b=%d", a, b);
    return 0;
}
