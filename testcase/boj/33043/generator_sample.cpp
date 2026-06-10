#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

vector<string> allTiles() {
    vector<string> tiles;
    for (char suit : string("mps")) {
        for (int rank = 1; rank <= 9; ++rank) {
            tiles.push_back(to_string(rank) + suit);
        }
    }
    for (int rank = 1; rank <= 7; ++rank) {
        tiles.push_back(to_string(rank) + "z");
    }
    return tiles;
}

void printCase(const vector<string>& hand) {
    println((int)hand.size());
    for (int i = 0; i < (int)hand.size(); ++i) {
        if (i) cout << ' ';
        cout << hand[i];
    }
    cout << '\n';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> tiles = allTiles();
    shuffle(tiles.begin(), tiles.end());

    vector<string> hand;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) hand.push_back(tiles[i]);
    } else if (mode == 1) {
        int distinct = rnd.next(5, 20);
        for (int i = 0; i < distinct; ++i) {
            int copies = rnd.next(1, 4);
            for (int j = 0; j < copies; ++j) hand.push_back(tiles[i]);
        }
        shuffle(hand.begin(), hand.end());
    } else if (mode == 2) {
        string target = tiles[0];
        int fillers = rnd.next(0, 12);
        for (int i = 0; i < 4; ++i) hand.push_back(target);
        for (int i = 0; i < fillers; ++i) hand.push_back(tiles[1 + i % 20]);
        shuffle(hand.begin(), hand.end());
        hand.push_back(target);
    } else if (mode == 3) {
        string target = tiles[0];
        int gap = rnd.next(1, 8);
        for (int i = 0; i < 5; ++i) {
            hand.push_back(target);
            for (int j = 0; j < gap; ++j) {
                hand.push_back(tiles[1 + rnd.next(20)]);
            }
        }
        if (rnd.next(0, 1)) shuffle(hand.begin(), hand.end());
    } else if (mode == 4) {
        int groups = rnd.next(2, 5);
        for (int i = 0; i < groups; ++i) {
            int copies = rnd.next(5, 8);
            for (int j = 0; j < copies; ++j) hand.push_back(tiles[i]);
        }
        int fillers = rnd.next(0, 15);
        for (int i = 0; i < fillers; ++i) hand.push_back(tiles[groups + i % 20]);
        shuffle(hand.begin(), hand.end());
    } else {
        int n = rnd.next(30, 90);
        for (int i = 0; i < n; ++i) {
            int tileIndex;
            if (rnd.next(0, 99) < 65) {
                tileIndex = rnd.next(0, min(8, (int)tiles.size() - 1));
            } else {
                tileIndex = rnd.next(0, (int)tiles.size() - 1);
            }
            hand.push_back(tiles[tileIndex]);
        }
    }

    printCase(hand);
    return 0;
}
