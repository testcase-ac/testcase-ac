#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Base colors and stickers
    vector<char> colors = {'B','G','O','R','W','Y'};
    vector<char> stickers;
    for (char c : colors)
        for (int i = 0; i < 4; i++)
            stickers.push_back(c);

    // Hyper-parameter: sometimes skip global shuffle to create clustered colors
    double shuffleProb = rnd.next(0.0, 1.0);
    if (shuffleProb < 0.9) {
        shuffle(stickers.begin(), stickers.end());
    }

    // Output 8 pieces
    for (int i = 0; i < 8; i++) {
        vector<char> piece = {
            stickers[3*i],
            stickers[3*i + 1],
            stickers[3*i + 2]
        };
        // Hyper-parameter: sometimes locally shuffle the order of stickers on a piece
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            // full shuffle
            shuffle(piece.begin(), piece.end());
        } else if (mode == 1) {
            // swap two random positions
            int a = rnd.next(0, 2), b = rnd.next(0, 2);
            swap(piece[a], piece[b]);
        }
        // mode == 2: keep original order

        // Print one piece (top, left, right)
        println(piece[0], piece[1], piece[2]);
    }

    return 0;
}
