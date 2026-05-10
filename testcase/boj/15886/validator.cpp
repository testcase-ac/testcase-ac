#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // 2. Read the map string S
    string S = inf.readToken("[EW]{"+to_string(N)+"}", "S");
    inf.readEoln();

    // 3. Check that "지도를 벗어나는 경우는 없다." (No out-of-bounds movement is possible)
    // That is: For every position x (1-based, 1 <= x <= N):
    //   - If S[x-1] == 'E', then x+1 <= N (i.e., x != N)
    //   - If S[x-1] == 'W', then x-1 >= 1 (i.e., x != 1)
    // So:
    //   - S[0] != 'W'
    //   - S[N-1] != 'E'
    ensuref(S[0] != 'W', "S[1] is 'W', which would move out of bounds left from position 1.");
    ensuref(S[N-1] != 'E', "S[N] is 'E', which would move out of bounds right from position N.");

    inf.readEof();
}
