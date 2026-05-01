#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXLEN = 10;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        string nick = inf.readToken("[a-z]{1,10}", "nickname");
        inf.readEoln();
        // Length and character constraints already ensured by regex:
        // - only lowercase letters
        // - length between 1 and 10
    }

    inf.readEof();
}
