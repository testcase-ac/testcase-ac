#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

char randomHand() {
    static const string h = "RPS";
    return h[rnd.next(0, 2)];
}

string randomString(int k) {
    string s(k, 'R');
    for (int i = 0; i < k; ++i)
        s[i] = randomHand();
    return s;
}

char beat(char c) {
    if (c == 'R') return 'P';
    if (c == 'P') return 'S';
    return 'R'; // c == 'S'
}

vector<string> genRandom(int N, int k) {
    vector<string> v(N);
    for (int i = 0; i < N; ++i)
        v[i] = randomString(k);
    return v;
}

// Always ends in a draw (winner 0)
vector<string> genTie(int N, int k) {
    vector<string> v(N);
    if (N >= 3 && rnd.next(0, 1) == 1) {
        // 3-cycle: R, P, S constant -> all three moves every round
        v[0] = string(k, 'R');
        v[1] = string(k, 'P');
        v[2] = string(k, 'S');
        for (int i = 3; i < N; ++i)
            v[i] = randomString(k);
    } else {
        // All robots identical
        string base = randomString(k);
        for (int i = 0; i < N; ++i)
            v[i] = base;
    }
    return v;
}

// One champion vs clones: winner appears at round winRound (1..k)
vector<string> genChampionVsClones(int N, int k, int winRound) {
    vector<string> v(N);
    string base = randomString(k);
    for (int i = 0; i < N; ++i)
        v[i] = base;

    int champ = rnd.next(0, N - 1);
    string champS = base;
    int t = winRound - 1; // first t rounds are ties
    for (int i = t; i < k; ++i)
        champS[i] = beat(base[i]);
    v[champ] = champS;
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 3);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Choose N with some diversity: small/mid/large
        int nType = rnd.next(0, 2);
        int N;
        if (nType == 0) N = rnd.next(2, 4);
        else if (nType == 1) N = rnd.next(5, 7);
        else N = rnd.next(8, 10);

        // Choose k with some diversity: short/mid/long (but <= 15)
        int kType = rnd.next(0, 2);
        int k;
        if (kType == 0) k = rnd.next(3, 5);
        else if (kType == 1) k = rnd.next(6, 10);
        else k = rnd.next(11, 15);

        // Scenario selection:
        // 0: fully random
        // 1: guaranteed draw
        // 2: early winner (before last round)
        // 3: winner at last round
        int scenario = rnd.next(0, 9);
        vector<string> robots;

        if (scenario <= 4) {
            // 0-4: mostly random
            robots = genRandom(N, k);
        } else if (scenario <= 6) {
            // 5-6: draw
            robots = genTie(N, k);
        } else if (scenario == 7) {
            // early winner (ensure k >= 3 -> winRound in [1, k-1])
            int winRound = rnd.next(1, max(1, k - 1));
            robots = genChampionVsClones(N, k, winRound);
        } else {
            // 8-9: winner decided at last round
            int winRound = k;
            robots = genChampionVsClones(N, k, winRound);
        }

        println(N);
        for (int i = 0; i < N; ++i)
            println(robots[i]);
    }

    return 0;
}
