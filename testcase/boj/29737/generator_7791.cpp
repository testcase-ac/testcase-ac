#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for variability
    int N = rnd.next(1, 10);
    int W = rnd.next(1, 10);

    println(N, W);

    set<string> usedNames;
    string letters = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < N; i++) {
        // Generate unique lowercase name
        string name;
        do {
            int len = rnd.next(3, 8);
            name.clear();
            for (int k = 0; k < len; k++) {
                name += rnd.any(letters);
            }
        } while (usedNames.count(name));
        usedNames.insert(name);
        println(name);

        int days = 7 * W;
        int fmax = days / 3; // up to a third frozen
        int fcount = rnd.next(0, fmax);

        // Choose freeze days
        vector<int> idx(days);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        vector<char> daysChar(days, '?');
        for (int j = 0; j < fcount; j++) {
            daysChar[idx[j]] = 'F';
        }
        // Fill others: O ~70%, X ~30%
        for (int j = fcount; j < days; j++) {
            int p = rnd.next(0, 9);
            daysChar[idx[j]] = (p < 7 ? 'O' : 'X');
        }

        // Print 7 rows of W chars each (row i, col j -> day 7*j + i)
        for (int r = 0; r < 7; r++) {
            string row;
            row.reserve(W);
            for (int c = 0; c < W; c++) {
                int pos = 7 * c + r;
                row += daysChar[pos];
            }
            println(row);
        }
    }

    return 0;
}
