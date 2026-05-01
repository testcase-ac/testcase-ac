#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cows, foods, drinks
    int N = rnd.next(1, 10);
    int F = rnd.next(1, 10);
    int D = rnd.next(1, 10);
    // Output header
    println(N, F, D);
    // For each cow, sample preferences with variability
    for (int i = 0; i < N; i++) {
        // Bias parameter for food and drink preferences
        int tF = rnd.next(-2, 2);
        int tD = rnd.next(-2, 2);
        // Fi in [1..F], Di in [1..D] using weighted sampling
        int Fi = rnd.wnext(F, tF) + 1;
        int Di = rnd.wnext(D, tD) + 1;
        // Sample distinct foods
        vector<int> foods(F);
        iota(foods.begin(), foods.end(), 1);
        shuffle(foods.begin(), foods.end());
        foods.resize(Fi);
        // Sample distinct drinks
        vector<int> drinks(D);
        iota(drinks.begin(), drinks.end(), 1);
        shuffle(drinks.begin(), drinks.end());
        drinks.resize(Di);
        // Print this cow's line
        printf("%d %d", Fi, Di);
        for (int x : foods)  printf(" %d", x);
        for (int x : drinks) printf(" %d", x);
        printf("\n");
    }
    return 0;
}
