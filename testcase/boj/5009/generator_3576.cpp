#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter: bias small, medium, or large n
    int biasN = rnd.next(-1, 1); 
    int n = rnd.wnext(9, biasN) + 2; // Generates n in [2,10]
    println(n);
    // Hyperparameter: teacher bias (-1 -> favor 2, 0 -> uniform, +1 -> favor 0)
    int teacherBias = rnd.next(-1, 1);
    // Hyperparameter: probability to shuffle full random
    double shuffleProb = rnd.next();
    
    for (int i = 1; i <= n; i++) {
        // Previous teacher assignment with bias
        int prev = rnd.wnext(3, teacherBias);
        // Build preference list excluding self
        vector<int> pref;
        for (int j = 1; j <= n; j++) {
            if (j != i) pref.push_back(j);
        }
        // Randomly decide to shuffle according to hyperparameter
        if (rnd.next() < shuffleProb) {
            shuffle(pref.begin(), pref.end());
        }
        // Occasionally reverse to create reverse-ordered preferences
        if (rnd.next() < 0.3) {
            reverse(pref.begin(), pref.end());
        }
        // Print line: prev teacher then permutation
        printf("%d", prev);
        for (int x : pref) {
            printf(" %d", x);
        }
        printf("\n");
    }
    return 0;
}
