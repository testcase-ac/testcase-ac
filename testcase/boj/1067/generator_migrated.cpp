#include <iostream>
#include <vector>
#include <random>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(0);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 99);

    int n = dis(gen)/3+1;
    cout << n << "\n";
    vector<int> X(n), Y(n);
    for (int i = 0; i < n; ++i) {
        X[i] = dis(gen);
    }
    for (int i = 0; i < n; ++i) {
        Y[i] = dis(gen);
    }
    for (int i = 0; i < n; ++i) {
        cout << X[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < n; ++i) {
        cout << Y[i] << " ";
    }
    cout << "\n";
    return 0;
}
