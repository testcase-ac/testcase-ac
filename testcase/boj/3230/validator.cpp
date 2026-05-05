#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(3, 100, "N");
    inf.readSpace();
    int M = inf.readInt(3, N, "M");
    inf.readEoln();

    // Read first race: N lines, each is an integer in [1, N]
    vector<int> first_race_ranks(N);
    for (int i = 0; i < N; ++i) {
        first_race_ranks[i] = inf.readInt(1, N, "first_race_rank");
        inf.readEoln();
    }

    // Find all players whose first race rank is in [1, M]
    // Their order in the second race is: for rank = M downto 1,
    // for all players with that rank (in increasing player number)
    vector<int> eligible_players;
    for (int rank = M; rank >= 1; --rank) {
        for (int i = 0; i < N; ++i) {
            if (first_race_ranks[i] == rank) {
                eligible_players.push_back(i + 1); // player numbers are 1-based
            }
        }
    }
    // There must be at least M players with rank in [1, M]
    ensuref((int)eligible_players.size() >= M,
        "Number of players with first race rank in [1, M] is %d, but M = %d",
        (int)eligible_players.size(), M);

    // Only the first M eligible players participate in the second race
    // (If more than M, only the first M in the described order are chosen)
    eligible_players.resize(M);

    // Read second race: M lines, each is an integer in [1, M]
    vector<int> second_race_ranks(M);
    for (int i = 0; i < M; ++i) {
        second_race_ranks[i] = inf.readInt(1, M, "second_race_rank");
        inf.readEoln();
    }

    inf.readEof();
}
