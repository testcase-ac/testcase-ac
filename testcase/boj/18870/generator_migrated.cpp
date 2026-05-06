#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-1000000000, 1000000000);
    uniform_int_distribution<> n_dist(1, 20);

    int N = n_dist(gen);
    vector<int> X(N);
    set<int> unique_values;

    for (int i = 0; i < N; ++i) {
        int x = dist(gen);
        unique_values.insert(x);
    }

    vector<int> unique_X(unique_values.begin(), unique_values.end());
    N = unique_X.size();

    cout << N << "\n";
    for (int i = 0; i < N; ++i) {
        cout << unique_X[i] << " ";
    }
}
