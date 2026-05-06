#include <iostream>
#include <random>
#include <vector>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> size_dis(1, 8);
    int N = size_dis(gen);
    int M = size_dis(gen);
    uniform_int_distribution<> value_dis(-100, 100);

    cout << N << " " << M << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << value_dis(gen) << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << value_dis(gen) << " ";
        }
        cout << endl;
    } return 0;
}
