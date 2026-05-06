#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> n_dis(1, 20);
    uniform_int_distribution<> digit_dis(0, 9);

    int N = n_dis(gen);
    cout << N << endl;

    string number = "";
    for (int i = 0; i < N; ++i) {
        number += to_string(digit_dis(gen));
    }

    cout << number << endl;
    return 0;
}
