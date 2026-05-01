#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: number of participants k (3 to 12)
    int k = rnd.next(3, 12);
    // Number of rows n (3 to 10)
    int n = rnd.next(3, 10);
    // Which row is hidden
    int hidden = rnd.next(0, n - 1);

    // Build full ladder with no adjacent bars
    vector<vector<int>> ladder(n, vector<int>(k - 1, 0));
    for (int i = 0; i < n; i++) {
        // Density type: sparse, medium, dense
        int dt = rnd.next(0, 2);
        int pd;
        if (dt == 0) pd = rnd.next(0, 30);
        else if (dt == 1) pd = rnd.next(30, 70);
        else pd = rnd.next(70, 100);
        double p = pd / 100.0;
        bool prev = false;
        for (int j = 0; j < k - 1; j++) {
            if (prev) {
                ladder[i][j] = 0;
                prev = false;
            } else {
                if (rnd.next() < p) {
                    ladder[i][j] = 1;
                    prev = true;
                } else {
                    ladder[i][j] = 0;
                }
            }
        }
    }

    // Compute final permutation after full ladder
    vector<int> perm(k);
    for (int i = 0; i < k; i++) perm[i] = i;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k - 1; j++) {
            if (ladder[i][j]) {
                swap(perm[j], perm[j + 1]);
            }
        }
    }

    // Build final order string
    string finalOrder;
    for (int i = 0; i < k; i++) {
        finalOrder.push_back(char('A' + perm[i]));
    }

    // Output
    println(k);
    println(n);
    println(finalOrder);
    for (int i = 0; i < n; i++) {
        if (i == hidden) {
            // hidden row
            println(string(k - 1, '?'));
        } else {
            string row;
            row.reserve(k - 1);
            for (int j = 0; j < k - 1; j++) {
                row.push_back(ladder[i][j] ? '-' : '*');
            }
            println(row);
        }
    }
    return 0;
}
