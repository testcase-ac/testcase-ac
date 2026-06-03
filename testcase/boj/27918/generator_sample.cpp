#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<char> rounds;

    if (mode == 0) {
        n = rnd.next(1, 6);
        char winner = rnd.any(string("DP"));
        rounds.assign(n, winner);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        char first = rnd.any(string("DP"));
        for (int i = 0; i < n; ++i) {
            rounds.push_back((i % 2 == 0) == (first == 'D') ? 'D' : 'P');
        }
    } else if (mode == 2) {
        int pairs = rnd.next(1, 12);
        n = pairs * 2 + rnd.next(1, 4);
        char first = rnd.any(string("DP"));
        for (int i = 0; i < pairs * 2; ++i) {
            rounds.push_back((i % 2 == 0) == (first == 'D') ? 'D' : 'P');
        }
        char closer = rnd.any(string("DP"));
        while ((int)rounds.size() < n) {
            rounds.push_back(closer);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 40);
        char favorite = rnd.any(string("DP"));
        int favoriteWeight = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            rounds.push_back(rnd.next(1, favoriteWeight + 1) <= favoriteWeight ? favorite : (favorite == 'D' ? 'P' : 'D'));
        }
    } else if (mode == 4) {
        n = rnd.next(20, 120);
        int block = rnd.next(1, 5);
        char current = rnd.any(string("DP"));
        for (int i = 0; i < n; ++i) {
            if (i > 0 && i % block == 0) current = current == 'D' ? 'P' : 'D';
            rounds.push_back(current);
        }
    } else {
        n = rnd.any(vector<int>{99990, 99999, 100000});
        char first = rnd.any(string("DP"));
        for (int i = 0; i < n; ++i) {
            rounds.push_back((i % 2 == 0) == (first == 'D') ? 'D' : 'P');
        }
    }

    println(n);
    for (char round : rounds) {
        println(string(1, round));
    }

    return 0;
}
