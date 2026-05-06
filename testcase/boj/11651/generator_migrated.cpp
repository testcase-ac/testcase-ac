#include <iostream>
#include <random>
#include <set>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> ng(1, 15);
    uniform_int_distribution<> xg(-100000, 100000);
    set<pair<int, int>> points;
    int n = ng(gen);
    cout << n << "\n";
    while (points.size()<n) {
        int x = xg(gen);
        int y = xg(gen);
        points.insert({x, y});
    }
    for (auto p : points) {
        cout << p.first << ' ' << p.second << "\n";
    }
}
