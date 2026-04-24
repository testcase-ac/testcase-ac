#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int hamming(const vector<string>& A, const vector<string>& B) {
    int diff = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 7; j++)
            if (A[i][j] != B[i][j]) diff++;
    return diff;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of pictures
    int N = rnd.next(2, 10);
    // Fix probability to avoid extremes
    double pX = 0.5;
    // Target minimum distance between the closest pair
    int d_target = rnd.wnext(10, -2); // bias towards small distances [0..9]

    // Generate a base picture
    vector<string> base(5, string(7, '.'));
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 7; j++)
            base[i][j] = (rnd.next() < pX ? 'X' : '.');

    // Prepare pic2 by flipping exactly d_target bits of base
    vector<int> pos(35);
    iota(pos.begin(), pos.end(), 0);
    shuffle(pos.begin(), pos.end());
    vector<string> pic2 = base;
    for (int k = 0; k < d_target; k++) {
        int idx = pos[k];
        int r = idx / 7, c = idx % 7;
        pic2[r][c] = (pic2[r][c] == 'X' ? '.' : 'X');
    }

    // Base container of the first two pics
    vector<vector<string>> basePics;
    basePics.push_back(base);
    basePics.push_back(pic2);

    // Now generate the rest ensuring no other pair has distance <= d_target
    vector<vector<string>> pics;
    while (true) {
        pics = basePics;
        bool failed = false;
        for (int i = 2; i < N; i++) {
            bool placed = false;
            int tries = 0;
            while (!placed && tries < 500) {
                tries++;
                vector<string> cand(5, string(7, '.'));
                for (int r = 0; r < 5; r++)
                    for (int c = 0; c < 7; c++)
                        cand[r][c] = (rnd.next() < pX ? 'X' : '.');
                bool ok = true;
                for (auto &ex : pics) {
                    if (hamming(cand, ex) <= d_target) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    pics.push_back(cand);
                    placed = true;
                }
            }
            if (!placed) {
                failed = true;
                break;
            }
        }
        if (!failed) break;
        // else retry entire generation of extras
    }

    // Output
    println(N);
    for (auto &pic : pics) {
        for (int r = 0; r < 5; r++) {
            printf("%s\n", pic[r].c_str());
        }
    }
    return 0;
}
