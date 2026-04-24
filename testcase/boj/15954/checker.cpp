#include "testlib.h"
#include <string>
using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int cnt = 0;
    double jury_ans = 0, part_ans = 0;

    // Read all numbers from jury and participant outputs (should be exactly one)
    while (!ans.seekEof()) {
        cnt++;
        jury_ans = ans.readDouble();
        part_ans = ouf.readDouble();
        if (!doubleCompare(jury_ans, part_ans, EPS)) {
            quitf(_wa,
                  "%d%s number differs - expected: '%.10f', found: '%.10f', error = '%.10f'",
                  cnt, englishEnding(cnt).c_str(),
                  jury_ans, part_ans, doubleDelta(jury_ans, part_ans));
        }
    }

    if (cnt == 0) {
        quitf(_wa, "no answer found");
    }
    if (cnt > 1) {
        // Problem expects a single number
        quitf(_wa, "too many numbers: found %d, expected 1", cnt);
    }

    // If everything is fine, report OK
    quitf(_ok, "answer = '%.10f'", part_ans);
}
