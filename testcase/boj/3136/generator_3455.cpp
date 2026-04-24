#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a pattern type for diversity
    int type = rnd.next(0, 5);
    string moves;

    if (type == 0) {
        // Horizontal line
        int N = rnd.next(1, 20);
        char c = rnd.next(0, 1) ? '2' : '6'; // 2 = right, 6 = left
        moves = string(N, c);
    }
    else if (type == 1) {
        // Vertical line
        int N = rnd.next(1, 20);
        char c = rnd.next(0, 1) ? '0' : '4'; // 0 = up, 4 = down
        moves = string(N, c);
    }
    else if (type == 2) {
        // Random walk
        int N = rnd.next(1, 20);
        for (int i = 0; i < N; i++) {
            moves.push_back(char('0' + rnd.next(0, 7)));
        }
    }
    else if (type == 3) {
        // Rectangle loop
        int w = rnd.next(2, 5);
        int h = rnd.next(2, 5);
        for (int i = 0; i < w; i++) moves.push_back('2');
        for (int i = 0; i < h; i++) moves.push_back('4');
        for (int i = 0; i < w; i++) moves.push_back('6');
        for (int i = 0; i < h; i++) moves.push_back('0');
    }
    else if (type == 4) {
        // Zigzag
        int s = rnd.next(1, 5);
        for (int i = 0; i < s; i++) {
            moves.push_back('0'); // up
            moves.push_back('2'); // right
            moves.push_back('4'); // down
            moves.push_back('2'); // right
        }
    }
    else {
        // Star shape: out-and-back in four directions
        vector<pair<int,int>> dirs = {{0,4}, {6,2}};
        for (auto &p : dirs) {
            int len = rnd.next(1, 2);
            for (int i = 0; i < len; i++) moves.push_back(char('0' + p.first));
            for (int i = 0; i < len; i++) moves.push_back(char('0' + p.second));
        }
    }

    int N = moves.size();
    // Ensure at least 1 move
    if (N == 0) {
        moves.push_back(char('0' + rnd.next(0,7)));
        N = 1;
    }

    // Output
    println(N);
    printf("%s\n", moves.c_str());
    return 0;
}
