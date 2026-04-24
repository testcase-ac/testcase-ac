#include "testlib.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = 1; // Number of test cases (fixed to 1 for simplicity)
    cout << t << endl;

    int n = rnd.next(0, 5); // Number of convenience stores (0 to 5)
    cout << n << endl;

    // Generate coordinates for home, convenience stores, and festival
    vector<pair<int, int>> coords;
    for (int i = 0; i < n + 2; ++i) {
        int x = rnd.next(-1000, 1000); // x coordinate (-1000 to 1000)
        int y = rnd.next(-1000, 1000); // y coordinate (-1000 to 1000)
        coords.push_back({x, y});
    }

    // Print the coordinates
    for (const auto& coord : coords) {
        cout << coord.first << " " << coord.second << endl;
    }

    return 0;
}
