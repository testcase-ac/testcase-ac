#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);

    int M = dis(gen);
    int N = dis(gen);

    if (M > N) swap(M, N);

    cout << M << endl;
    cout << N << endl;

    return 0;
}
