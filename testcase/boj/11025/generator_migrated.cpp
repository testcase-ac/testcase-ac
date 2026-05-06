#include <iostream>
#include <random>
#include <ctime>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis_n(1, 5000000);
    int N = dis_n(gen);
    uniform_int_distribution<> dis_k(1, N);
    int K = dis_k(gen);
    cout << N << " " << K << endl;
    return 0;
}
