#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    int x1 = dis(gen), y1 = dis(gen);
    int x2 = dis(gen), y2 = dis(gen);

    while (x1 == x2 || y1 == y2) {
        x2 = dis(gen);
        y2 = dis(gen);
    }

    cout << x1 << " " << y1 << endl;
    cout << x1 << " " << y2 << endl;
    cout << x2 << " " << y1 << endl;

    return 0;
}
