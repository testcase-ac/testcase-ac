#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cards
    int n = rnd.next(4, 10);
    // Number to pick
    int k = rnd.next(2, min(4, n));
    // Hyper-parameter for distinct count bias
    int t = rnd.next(-2, 2);
    // Determine how many unique values we'll generate (1..n)
    int distinctCount = rnd.wnext(n, t) + 1;
    // Probability to pick two-digit numbers
    double probTwo = rnd.next();
    // Generate distinct values
    set<int> used;
    vector<int> distinct;
    while ((int)distinct.size() < distinctCount) {
        int v;
        if (rnd.next() < probTwo)
            v = rnd.next(10, 99);
        else
            v = rnd.next(1, 9);
        if (!used.count(v)) {
            used.insert(v);
            distinct.push_back(v);
        }
    }
    // Build full list of n cards, allowing duplicates
    vector<int> cards = distinct;
    while ((int)cards.size() < n) {
        cards.push_back(rnd.any(distinct));
    }
    // Shuffle the card order
    shuffle(cards.begin(), cards.end());
    // Output in required format
    println(n);
    println(k);
    for (int x : cards) println(x);
    return 0;
}
