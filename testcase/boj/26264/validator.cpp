#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const string A = "bigdata";
    const string B = "security";
    const int LA = (int)A.size();
    const int LB = (int)B.size();

    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    string s = inf.readLine("[a-z]+", "answers");

    // Length must match exactly N answers consisting only of "bigdata" and "security".
    ensuref(!s.empty(), "answers string must be non-empty");
    ensuref((int)s.size() >= min(LA, LB),
            "answers string is too short to contain any valid token");

    // Greedy parsing from left to right, as implied by how the professor wrote answers.
    int cntBig = 0, cntSec = 0;
    int i = 0;
    int L = (int)s.size();

    while (i < L) {
        bool ok = false;
        if (i + LA <= L && s.compare(i, LA, A) == 0) {
            cntBig++;
            i += LA;
            ok = true;
        } else if (i + LB <= L && s.compare(i, LB, B) == 0) {
            cntSec++;
            i += LB;
            ok = true;
        }
        ensuref(ok, "answers string contains invalid segment starting at position %d (0-based)",
                i);
    }

    // Check the total number of parsed answers equals N
    ensuref(cntBig + cntSec == N,
            "total number of parsed answers (%d) does not match N (%d)",
            cntBig + cntSec, N);

    inf.readEof();
}
