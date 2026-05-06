#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 90);
    uniform_int_distribution<> num(0, 10);

    int n = num(gen) + 1;
    cout << n << endl;

    for (int i = 0; i < n; i++) {
        int x = dis(gen);
        int y = dis(gen);
        cout << x << " " << y << endl;
    }
}
