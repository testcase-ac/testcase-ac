#include <iostream>
#include <random>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> distN(1, 100);
    uniform_int_distribution<int> distC(1, 100);
    uniform_int_distribution<int> distK(0, 1000000000);

    int N = distN(gen);
    cout << N << endl;

    for (int i = 0; i < N; ++i) {
        int C = distC(gen);
        int K = distK(gen);
        cout << C << " " << K << endl;
    }
}
