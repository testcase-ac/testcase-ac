#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> corners = {"a1", "a8", "h1", "h8"};
    vector<string> edges = {
        "a2", "a3", "a4", "a5", "a6", "a7",
        "b1", "c1", "d1", "e1", "f1", "g1",
        "b8", "c8", "d8", "e8", "f8", "g8",
        "h2", "h3", "h4", "h5", "h6", "h7",
    };
    vector<string> nearEdges = {
        "b2", "b3", "b4", "b5", "b6", "b7",
        "c2", "d2", "e2", "f2", "g2",
        "c7", "d7", "e7", "f7", "g7",
        "g3", "g4", "g5", "g6",
    };

    int mode = rnd.next(0, 4);
    string square;
    if (mode == 0) {
        square = rnd.any(corners);
    } else if (mode == 1) {
        square = rnd.any(edges);
    } else if (mode == 2) {
        square = rnd.any(nearEdges);
    } else {
        char file = char('a' + rnd.next(0, 7));
        char rank = char('1' + rnd.next(0, 7));
        square = string() + file + rank;
    }

    println(square);
    return 0;
}
