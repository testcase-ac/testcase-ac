#include <iostream>
#include <random>
#include <ctime>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 5);
    uniform_int_distribution<> dis_size(1, 10);
    uniform_int_distribution<> dis_seat(0, 1);

    int C = dis(gen);
    cout << C << endl;

    for (int i = 0; i < C; ++i) {
        int N = dis_size(gen);
        int M = dis_size(gen);
        cout << N << " " << M << endl;

        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < M; ++k) {
                char seat = dis_seat(gen) == 0 ? '.' : 'x';
                cout << seat;
            }
            cout << endl;
        }
    }

    return 0;
}
