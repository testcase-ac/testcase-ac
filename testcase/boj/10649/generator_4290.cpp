#include "testlib.h"
#include <vector>
#include <tuple>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cows
    int N = rnd.next(2, 10);
    // Hyper-parameters for cow attributes
    int hMax = rnd.next(5, 15);       // max individual height
    int wMax = rnd.next(2, 10);       // max individual weight
    int slackMax = rnd.next(0, 10);   // max extra strength slack
    
    // Generate heights and weights
    vector<int> Hs(N), Ws(N);
    for (int i = 0; i < N; i++) {
        Hs[i] = rnd.next(1, hMax);
        Ws[i] = rnd.next(1, wMax);
    }
    // Total weight and height sums
    int totalWeight = accumulate(Ws.begin(), Ws.end(), 0);
    int totalHeight = accumulate(Hs.begin(), Hs.end(), 0);
    
    // Build cows with guaranteed support: strength >= totalWeight + slack
    vector<tuple<int,int,long long>> cows;
    for (int i = 0; i < N; i++) {
        long long slack = rnd.next(0, slackMax);
        long long strength = totalWeight + slack;
        cows.emplace_back(Hs[i], Ws[i], strength);
    }
    // Shuffle to avoid any order bias
    shuffle(cows.begin(), cows.end());
    
    // Decide if this case should be solvable
    bool possible = rnd.next(0, 1);
    int MarkH;
    if (possible) {
        // Pick a target height between 1 and totalHeight
        int lo = rnd.next(1, totalHeight);
        MarkH = rnd.next(lo, totalHeight);
    } else {
        // Make it impossible by exceeding total height
        MarkH = totalHeight + rnd.next(1, 10);
    }
    
    // Output
    println(N, MarkH);
    for (auto &c : cows) {
        println(get<0>(c), get<1>(c), get<2>(c));
    }
    return 0;
}
