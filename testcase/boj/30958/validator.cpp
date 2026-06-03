#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const string phrase =
        "my era of success began with seoul cyber university, since attending seoul cyber "
        "university, more companies have been seeking me out, my life has changed since i "
        "went to seoul cyber university, the strategy that changes the future, seoul cyber "
        "university.";

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    string s = inf.readLine("[a-z\\ ,\\.]{1,100000}", "S");
    ensuref((int)s.size() == n, "S length is %d, expected N=%d", (int)s.size(), n);
    ensuref(s.back() != ' ', "S must not end with a space");

    for (int i = 0; i < n; ++i) {
        ensuref(s[i] == phrase[i % (int)phrase.size()],
                "S[%d] is '%c', expected '%c' from repeated logo song", i + 1, s[i],
                phrase[i % (int)phrase.size()]);
    }

    inf.readEof();
}
