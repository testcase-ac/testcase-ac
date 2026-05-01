#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    vector<int> possible_n = {2, 4, 8, 16, 32};
    for (int tc = 0; tc < T; tc++) {
        int n = rnd.any(possible_n);
        // Ensure n is at least 2
        n = max(n, 2);
        // Create empty wins matrix: -1=unset, 0 = loses, 1 = wins
        vector<vector<int>> wins(n+1, vector<int>(n+1, -1));
        for (int i = 1; i <= n; i++) {
            wins[i][i] = 0;
        }
        // Team 1's outdegree: at least n/2
        int minWin = n/2;
        int d = rnd.next(minWin, n-1);
        // Choose A = teams that 1 beats
        vector<int> others;
        for (int i = 2; i <= n; i++) others.push_back(i);
        shuffle(others.begin(), others.end());
        vector<int> A(others.begin(), others.begin() + d);
        vector<int> B(others.begin() + d, others.end());
        // Set edges between 1 and others
        for (int x : A) {
            wins[1][x] = 1; wins[x][1] = 0;
        }
        for (int y : B) {
            wins[1][y] = 0; wins[y][1] = 1;
        }
        // For each y in B, ensure there is a pre-beater in A
        for (int y : B) {
            int p = rnd.any(A);
            wins[p][y] = 1;
            wins[y][p] = 0;
        }
        // Fill remaining unset matches randomly
        for (int i = 1; i <= n; i++) {
            for (int j = i+1; j <= n; j++) {
                if (wins[i][j] == -1) {
                    if (rnd.next(0,1)) {
                        wins[i][j] = 1;
                        wins[j][i] = 0;
                    } else {
                        wins[i][j] = 0;
                        wins[j][i] = 1;
                    }
                }
            }
        }
        // Output this test case
        println(n);
        for (int i = 1; i <= n; i++) {
            string s;
            s.reserve(n);
            for (int j = 1; j <= n; j++) {
                s.push_back(char('0' + wins[i][j]));
            }
            println(s);
        }
    }
    return 0;
}
