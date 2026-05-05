#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 500000;
    const int MAXK = 500000;
    const long long MAXV = 1000000000LL;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int K = inf.readInt(1, MAXK, "K");
    inf.readEoln();

    vector<long long> p = inf.readLongs(N, 0LL, MAXV, "p_i");
    inf.readEoln();
    vector<long long> t = inf.readLongs(N, 0LL, MAXV, "t_i");
    inf.readEoln();

    // No extra relation between p_i and t_i is stated, so do not enforce t_i >= p_i
    // All constraints from statement are already enforced by readLongs ranges.

    inf.readEof();
}
