#include "testlib.h"
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate dictionary size
    int D = rnd.next(5, 15);
    set<string> sx;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while ((int)sx.size() < D) {
        int len = rnd.next(4, 9);
        string w;
        for (int i = 0; i < len; ++i)
            w.push_back(rnd.any(alphabet));
        sx.insert(w);
    }
    vector<string> dict(sx.begin(), sx.end());
    // Already lex-sorted by set

    // Print dictionary
    for (auto &w : dict) println(w);
    println("-");

    // Generate puzzles
    int P = rnd.next(1, 4);
    vector<string> puzzles;
    for (int i = 0; i < P; ++i) {
        string board;
        if (rnd.next(0, 1) == 1) {
            // embed one dictionary word
            const string &w = rnd.any(dict);
            board = w;
            while ((int)board.size() < 9)
                board.push_back(rnd.any(alphabet));
        } else {
            // random letters
            for (int j = 0; j < 9; ++j)
                board.push_back(rnd.any(alphabet));
        }
        shuffle(board.begin(), board.end());
        puzzles.push_back(board);
    }
    for (auto &b : puzzles) println(b);
    println("#");

    return 0;
}
