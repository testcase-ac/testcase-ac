#include "testlib.h"
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and L
    int N = inf.readInt(3, 50, "N");
    inf.readSpace();
    int L = inf.readInt(0, 10000, "L");
    inf.readEoln();

    // 2. Read medals for each team
    vector<int> gold(N), silver(N), bronze(N);
    for (int i = 0; i < N; ++i) {
        gold[i] = inf.readInt(0, 10000, "gold");
        inf.readSpace();
        silver[i] = inf.readInt(0, 10000, "silver");
        inf.readSpace();
        bronze[i] = inf.readInt(0, 10000, "bronze");
        inf.readEoln();
    }

    // 3. No further input
    inf.readEof();

    // 4. Global property: In the remaining L games, all medals are awarded (i.e., 3 medals per game)
    // So, after the input, it's possible that the sum of gold/silver/bronze are not equal,
    // but in the remaining L games, all 3 medals are awarded per game.

    // Validate that L*3 medals can be distributed in the remaining games.
    // (No further validation needed here, as the input only gives current medals.)

    // 5. (Optional) Check that the sum of medals does not overflow
    // (Not strictly necessary, as each is <= 10000, N <= 50, so sum <= 500000)

    // 6. (Optional) Check that there are no negative medals (already checked by readInt)

    // 7. (Optional) Check that there are no leading zeros in medals (readInt already does this)

    // 8. (Optional) Check that the answer always exists (i.e., it's always possible for team 1 to win all L golds)
    // Since the problem says "각 팀은 경기당 최대 1개의 메달을 받을 수 있다", and there are N teams, N >= 3,
    // and in each game, 3 medals are awarded, so it's always possible for team 1 to win all L golds in the remaining games.

    // No further global validation is required.

    return 0;
}
