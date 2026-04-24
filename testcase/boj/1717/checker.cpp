#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int cnt = 0;
    // Read expected answers from jury (ans) and participant (ouf) one by one
    while (!ans.seekEof()) {
        cnt++;
        string ja = ans.readToken();  // jury's "YES"/"NO"
        string pa = ouf.readToken();  // participant's answer

        // compare case-insensitive
        string jlow = ja, plow = pa;
        transform(jlow.begin(), jlow.end(), jlow.begin(), ::tolower);
        transform(plow.begin(), plow.end(), plow.begin(), ::tolower);
        if (jlow != plow) {
            quitf(_wa, "Answer %d differs: expected '%s', found '%s'",
                  cnt, ja.c_str(), pa.c_str());
        }
    }
    // Ensure no extra tokens in participant output
    if (!ouf.seekEof()) {
        string extra = ouf.readToken();
        quitf(_wa, "Extraneous output: '%s'", extra.c_str());
    }
    quitf(_ok, "%d answers", cnt);
    return 0;
}
