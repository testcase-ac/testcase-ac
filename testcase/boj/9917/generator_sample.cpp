#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Game {
    int a;
    int b;
    int winner;
};

Game makeGame(int winner, int loser) {
    if (rnd.next(2) == 0) {
        return {winner, loser, winner};
    }
    return {loser, winner, winner};
}

void addWin(vector<Game>& games, int winner, int loser, int limit) {
    if (winner == loser || static_cast<int>(games.size()) >= limit) {
        return;
    }
    games.push_back(makeGame(winner, loser));
}

void addCycle(vector<Game>& games, const vector<int>& players, int limit) {
    for (int i = 0; i < static_cast<int>(players.size()); ++i) {
        addWin(games, players[i], players[(i + 1) % players.size()], limit);
    }
}

pair<int, int> scoresForWinner(bool firstWins) {
    int loserScore = rnd.next(0, 8);
    int winnerScore = rnd.next(loserScore + 1, 9);
    if (firstWins) {
        return {winnerScore, loserScore};
    }
    return {loserScore, winnerScore};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int maxGames = 30;
    vector<Game> games;

    vector<int> players(n);
    for (int i = 0; i < n; ++i) {
        players[i] = i + 1;
    }
    shuffle(players.begin(), players.end());

    if (mode == 0) {
        n = rnd.next(2, 10);
        players.resize(n);
        for (int i = 0; i < n; ++i) {
            players[i] = i + 1;
        }
        shuffle(players.begin(), players.end());

        int k = rnd.next(1, min(maxGames, n * (n - 1) / 2));
        vector<pair<int, int>> orderedPairs;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                orderedPairs.push_back({players[i], players[j]});
            }
        }
        shuffle(orderedPairs.begin(), orderedPairs.end());
        for (int i = 0; i < k; ++i) {
            addWin(games, orderedPairs[i].first, orderedPairs[i].second, maxGames);
        }
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        int cycleSize = rnd.next(3, min(n, 7));
        players.resize(n);
        for (int i = 0; i < n; ++i) {
            players[i] = i + 1;
        }
        shuffle(players.begin(), players.end());
        vector<int> cycle(players.begin(), players.begin() + cycleSize);
        addCycle(games, cycle, maxGames);

        int extra = rnd.next(0, min(12, maxGames - static_cast<int>(games.size())));
        for (int i = 0; i < extra; ++i) {
            int a = rnd.any(players);
            int b = rnd.any(players);
            while (a == b) {
                b = rnd.any(players);
            }
            addWin(games, a, b, maxGames);
        }
    } else if (mode == 2) {
        n = rnd.next(6, 14);
        players.resize(n);
        for (int i = 0; i < n; ++i) {
            players[i] = i + 1;
        }
        shuffle(players.begin(), players.end());

        addCycle(games, {players[0], players[1], players[2]}, maxGames);
        addCycle(games, {players[3], players[4], players[5]}, maxGames);
        if (n >= 8 && rnd.next(2) == 1) {
            addCycle(games, {players[2], players[6], players[7]}, maxGames);
        }

        int extra = rnd.next(0, min(10, maxGames - static_cast<int>(games.size())));
        for (int i = 0; i < extra; ++i) {
            int winner = rnd.any(players);
            int loser = rnd.any(players);
            while (winner == loser) {
                loser = rnd.any(players);
            }
            addWin(games, winner, loser, maxGames);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        int k = rnd.next(2, 30);
        for (int i = 0; i < k; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            while (a == b) {
                b = rnd.next(1, n);
            }
            int winner = (rnd.next(2) == 0 ? a : b);
            games.push_back({a, b, winner});
        }
    } else {
        n = rnd.next(2, 20);
        int k = rnd.next(1, 30);
        for (int i = 0; i < k; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            while (a == b) {
                b = rnd.next(1, n);
            }
            int winner = (rnd.next(2) == 0 ? a : b);
            games.push_back({a, b, winner});
        }
    }

    shuffle(games.begin(), games.end());
    println(n, static_cast<int>(games.size()));
    for (const Game& game : games) {
        bool firstWins = (game.a == game.winner);
        auto scores = scoresForWinner(firstWins);
        println(game.a, game.b, scores.first, scores.second);
    }

    return 0;
}
