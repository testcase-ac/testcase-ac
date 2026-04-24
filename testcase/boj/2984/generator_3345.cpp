#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of trucks
    int N = rnd.next(1, 10);

    // Hyper-parameter: range for entry points
    int extra_e = rnd.next(0, 10);
    int B_e = N + extra_e;  // ensures B_e >= N
    vector<int> entries(B_e);
    for (int i = 0; i < B_e; i++) entries[i] = i + 1;
    shuffle(entries.begin(), entries.end());
    entries.resize(N);

    // Hyper-parameter: range for exit points
    int extra_o = rnd.next(0, 10);
    int B_o = N + extra_o;  // ensures B_o >= N
    vector<int> exits(B_o);
    for (int i = 0; i < B_o; i++) exits[i] = i + 1;
    shuffle(exits.begin(), exits.end());
    exits.resize(N);

    // Make some exits equal to entries (allowed in input), avoiding duplicate exits
    set<int> exitSet(exits.begin(), exits.end());
    for (int i = 0; i < N; i++) {
        if (rnd.next(0, 9) < 3) { // ~30% chance
            int e_in = entries[i];
            int e_out = exits[i];
            if (e_in != e_out && exitSet.count(e_in) == 0) {
                exitSet.erase(e_out);
                exits[i] = e_in;
                exitSet.insert(e_in);
            }
        }
    }

    // Pair up and shuffle the order of trucks
    vector<pair<int,int>> trucks;
    for (int i = 0; i < N; i++) {
        trucks.emplace_back(entries[i], exits[i]);
    }
    shuffle(trucks.begin(), trucks.end());

    // Output
    println(N);
    for (auto &p : trucks) {
        println(p.first, p.second);
    }
    return 0;
}
