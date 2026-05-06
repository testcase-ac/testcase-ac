#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);
    uniform_int_distribution<> dis_count(1, 20);

    int N = dis_count(gen);
    cout << N << endl;

    for (int i = 0; i < N; ++i) {
        cout << dis(gen) << " ";
    }
    cout << endl;
    return 0;
}
