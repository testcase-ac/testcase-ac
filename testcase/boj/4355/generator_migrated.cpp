#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis_small(1, 1000000);
    uniform_int_distribution<> dis_large(1000001, 1000000000);
    uniform_int_distribution<> stop_dis(1, 10);

    int count = 0;
    
    while (true) {
        int n;
        if (count % 2 == 0) {
            n = dis_small(gen);
        } else {
            n = dis_large(gen);
        }

        cout << n << endl;
        count++;
        if (stop_dis(gen) == 1) {
            cout << 0 << endl;
            break;
        }
    }
    return 0;
}
