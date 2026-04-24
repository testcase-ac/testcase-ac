#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: 1 <= T <= 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        // Number of friendships F: 1 <= F <= 100000
        int F = inf.readInt(1, 100000, "F");
        inf.readEoln();

        // Each of the F lines: two user IDs, each 1..20 letters (A-Z, a-z)
        for (int i = 0; i < F; i++) {
            // first user name
            inf.readToken("[A-Za-z]{1,20}", "user1");
            inf.readSpace();
            // second user name
            inf.readToken("[A-Za-z]{1,20}", "user2");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
