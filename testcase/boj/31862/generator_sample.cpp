#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Game {
    int a;
    int b;
    int result;
};

int otherTeam(int n, int team) {
    int value = rnd.next(1, n - 1);
    if (value >= team) ++value;
    return value;
}

Game randomGame(int n, int forcedResult = -1) {
    int a = rnd.next(1, n);
    int b = otherTeam(n, a);
    if (rnd.next(2)) swap(a, b);
    int result = forcedResult == -1 ? rnd.next(0, 2) : forcedResult;
    return {a, b, result};
}

void addPlayedWin(vector<Game>& games, int winner, int loser) {
    if (rnd.next(2)) {
        games.push_back({winner, loser, 1});
    } else {
        games.push_back({loser, winner, 2});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    int k = rnd.next(1, n);
    vector<Game> games;

    if (mode == 0) {
        int m = rnd.next(1, 24);
        for (int i = 0; i < m; ++i) {
            games.push_back(randomGame(n));
        }
    } else if (mode == 1) {
        int unplayed = rnd.next(15, 20);
        int played = rnd.next(0, 8);
        for (int i = 0; i < unplayed; ++i) {
            games.push_back(randomGame(n, 0));
        }
        for (int i = 0; i < played; ++i) {
            games.push_back(randomGame(n, rnd.next(1, 2)));
        }
    } else if (mode == 2) {
        if (n < 3) n = 3;
        k = rnd.next(1, n);
        vector<int> others;
        for (int i = 1; i <= n; ++i) {
            if (i != k) others.push_back(i);
        }
        int m = rnd.next(3, 18);
        for (int i = 0; i < m; ++i) {
            int a = rnd.any(others);
            int b = rnd.any(others);
            while (a == b) b = rnd.any(others);
            games.push_back({a, b, rnd.next(0, 2)});
        }
    } else if (mode == 3) {
        int rival = otherTeam(n, k);
        int support = otherTeam(n, rival);
        int kWins = rnd.next(0, 5);
        int rivalWins = rnd.next(kWins, kWins + 2);
        for (int i = 0; i < kWins; ++i) {
            addPlayedWin(games, k, otherTeam(n, k));
        }
        for (int i = 0; i < rivalWins; ++i) {
            addPlayedWin(games, rival, otherTeam(n, rival));
        }
        int unplayed = rnd.next(1, 10);
        for (int i = 0; i < unplayed; ++i) {
            int opponent = rnd.next(3) == 0 ? rival : otherTeam(n, k);
            games.push_back({k, opponent, 0});
        }
        if (support != k && support != rival && rnd.next(2)) {
            games.push_back({support, rival, 0});
        }
    } else {
        int leaders = rnd.next(2, min(n, 5));
        int baseline = rnd.next(1, 5);
        for (int team = 1; team <= leaders; ++team) {
            for (int i = 0; i < baseline; ++i) {
                addPlayedWin(games, team, otherTeam(n, team));
            }
        }
        int unplayed = rnd.next(1, 12);
        for (int i = 0; i < unplayed; ++i) {
            int a = rnd.next(1, leaders);
            int b = rnd.next(1, n);
            while (a == b) b = rnd.next(1, n);
            games.push_back({a, b, 0});
        }
        k = rnd.next(1, leaders);
    }

    shuffle(games.begin(), games.end());
    println(n, static_cast<int>(games.size()), k);
    for (const Game& game : games) {
        println(game.a, game.b, game.result);
    }

    return 0;
}
