#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> n_dist(2, 1000000);
    int N = n_dist(gen);
    uniform_int_distribution<> m_dist(1, N);
    int M = m_dist(gen);
    cout << N << " " << M;
}
