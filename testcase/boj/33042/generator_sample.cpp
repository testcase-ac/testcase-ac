#include "testlib.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

vector<string> allTiles() {
    vector<string> tiles;
    for (char suit : {'m', 'p', 's'}) {
        for (char rank = '1'; rank <= '9'; ++rank) {
            tiles.push_back(string() + rank + suit);
        }
    }
    for (char rank = '1'; rank <= '7'; ++rank) {
        tiles.push_back(string() + rank + 'z');
    }
    return tiles;
}

void appendRandomSafeTile(vector<string>& hand, const vector<string>& tiles, map<string, int>& count) {
    vector<string> candidates;
    for (const string& tile : tiles) {
        if (count[tile] < 4) {
            candidates.push_back(tile);
        }
    }
    string tile = rnd.any(candidates);
    hand.push_back(tile);
    ++count[tile];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> tiles = allTiles();
    shuffle(tiles.begin(), tiles.end());

    vector<string> hand;
    map<string, int> count;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            appendRandomSafeTile(hand, tiles, count);
        }
    } else if (mode == 1) {
        string target = rnd.any(tiles);
        int before = rnd.next(0, 4);
        for (int i = 0; i < before; ++i) {
            appendRandomSafeTile(hand, tiles, count);
        }
        for (int i = 0; i < 5; ++i) {
            hand.push_back(target);
        }
        int after = rnd.next(0, 8);
        for (int i = 0; i < after; ++i) {
            hand.push_back(rnd.any(tiles));
        }
    } else if (mode == 2) {
        string target = rnd.any(tiles);
        for (int i = 0; i < 4; ++i) {
            hand.push_back(target);
            ++count[target];
        }
        int filler = rnd.next(5, 40);
        for (int i = 0; i < filler; ++i) {
            appendRandomSafeTile(hand, tiles, count);
        }
        shuffle(hand.begin(), hand.end());
        hand.push_back(target);
    } else if (mode == 3) {
        string target = rnd.any(tiles);
        int n = rnd.next(5, 136);
        for (int i = 0; i < n; ++i) {
            hand.push_back(target);
        }
    } else if (mode == 4) {
        int groups = rnd.next(4, 34);
        for (int i = 0; i < groups; ++i) {
            int copies = rnd.next(1, 4);
            for (int j = 0; j < copies; ++j) {
                hand.push_back(tiles[i]);
            }
        }
        shuffle(hand.begin(), hand.end());
    } else {
        string target = rnd.any(tiles);
        int prefix = rnd.next(0, 30);
        for (int i = 0; i < prefix; ++i) {
            appendRandomSafeTile(hand, tiles, count);
        }
        for (int i = 0; i < 4; ++i) {
            hand.push_back(target);
        }
        int split = rnd.next(0, 20);
        for (int i = 0; i < split; ++i) {
            appendRandomSafeTile(hand, tiles, count);
        }
        hand.push_back(target);
    }

    println((int)hand.size());
    println(hand);

    return 0;
}
