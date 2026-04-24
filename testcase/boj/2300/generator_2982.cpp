#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of buildings
    int N = rnd.next(1, 10);
    // X coordinate range magnitude (ensure enough unique x)
    int Xmax = rnd.next(N, 50);
    // Y coordinate magnitude range
    int Ymax = rnd.next(1, 50);
    // Bias for positive vs negative y
    int posBias = rnd.next(0, 100);

    // Generate N unique building coordinates
    set<pair<int,int>> S;
    while ((int)S.size() < N) {
        int x = rnd.next(-Xmax, Xmax);
        int sign = (rnd.next(0, 99) < posBias ? 1 : -1);
        int y = sign * rnd.next(1, Ymax);
        S.insert({x, y});
    }

    // Shuffle the order
    vector<pair<int,int>> buildings(S.begin(), S.end());
    shuffle(buildings.begin(), buildings.end());

    // Output
    println(N);
    for (auto &p : buildings) {
        println(p.first, p.second);
    }
    return 0;
}
