#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> n_dis(1, 10);
    uniform_int_distribution<> coord_dis(-10000, 10000);

    int n = n_dis(gen);
    cout << n << endl;

    for (int i = 0; i < n; i++) {
        int x = coord_dis(gen);
        int y = coord_dis(gen);
        cout << x << " " << y << endl;
    }
    return 0;
}
