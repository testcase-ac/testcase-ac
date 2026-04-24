#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Number of horizontal and vertical words
        int H = rnd.next(1, 4);
        int V = rnd.next(1, 4);
        println(H, V);

        // Grid max coordinate
        int MAXC = 10;

        // Generate distinct rows for horizontals
        vector<int> allY;
        for (int y = 0; y <= MAXC; ++y) allY.push_back(y);
        shuffle(allY.begin(), allY.end());
        vector<int> h_y(allY.begin(), allY.begin() + H);

        // Generate distinct cols for verticals
        vector<int> allX;
        for (int x = 0; x <= MAXC; ++x) allX.push_back(x);
        shuffle(allX.begin(), allX.end());
        vector<int> v_x(allX.begin(), allX.begin() + V);

        // Random lengths
        vector<int> h_len(H), v_len(V);
        for (int i = 0; i < H; ++i) h_len[i] = rnd.next(1, 5);
        for (int i = 0; i < V; ++i) v_len[i] = rnd.next(1, 5);

        // Starting positions
        vector<int> h_x(H), v_y(V);
        for (int i = 0; i < H; ++i) {
            int maxStart = MAXC - h_len[i];
            h_x[i] = rnd.next(0, maxStart);
        }
        for (int j = 0; j < V; ++j) {
            int maxStart = MAXC - v_len[j];
            v_y[j] = rnd.next(0, maxStart);
        }

        // Initialize words with placeholders
        vector<string> h_word(H), v_word(V);
        for (int i = 0; i < H; ++i) h_word[i] = string(h_len[i], '?');
        for (int j = 0; j < V; ++j) v_word[j] = string(v_len[j], '?');

        // For each crossing, randomly set it to conflict or match
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < V; ++j) {
                int xi = h_x[i], yi = h_y[i], li = h_len[i];
                int xj = v_x[j], yj = v_y[j], lj = v_len[j];
                // Check intersection
                if (xj >= xi && xj < xi + li && yi >= yj && yi < yj + lj) {
                    int posH = xj - xi;
                    int posV = yi - yj;
                    bool makeMatch = rnd.next(0, 1) == 0;
                    if (makeMatch) {
                        char c = char(rnd.next('A', 'Z'));
                        h_word[i][posH] = c;
                        v_word[j][posV] = c;
                    } else {
                        char c1 = char(rnd.next('A', 'Z'));
                        char c2 = char(rnd.next('A', 'Z'));
                        if (c1 == c2) {
                            c2 = char('A' + (c1 - 'A' + 1) % 26);
                        }
                        h_word[i][posH] = c1;
                        v_word[j][posV] = c2;
                    }
                }
            }
        }

        // Fill remaining '?' with random letters
        for (int i = 0; i < H; ++i)
            for (char &c : h_word[i])
                if (c == '?') c = char(rnd.next('A', 'Z'));
        for (int j = 0; j < V; ++j)
            for (char &c : v_word[j])
                if (c == '?') c = char(rnd.next('A', 'Z'));

        // Output horizontals
        for (int i = 0; i < H; ++i) {
            println(h_x[i], h_y[i], h_word[i]);
        }
        // Output verticals
        for (int j = 0; j < V; ++j) {
            println(v_x[j], v_y[j], v_word[j]);
        }
    }

    return 0;
}
