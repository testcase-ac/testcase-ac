#include <iostream>
#include <random>
#include <string>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> cmd_dist(1, 8);
    uniform_int_distribution<int> tc_dist(1, 100);
    uniform_int_distribution<int> num_dist(1, 100000);
    int n = tc_dist(gen);
    
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        int cmd = cmd_dist(gen);
        if (cmd==1||cmd==7||cmd==8) {
            cout << "push " << num_dist(gen) << endl;
        } else if (cmd == 2) {
            cout << "pop" << endl;
        } else if (cmd == 3) {
            cout << "size" << endl;
        } else if (cmd == 4) {
            cout << "empty" << endl;
        } else if (cmd == 5) {
            // front
            cout << "front" << endl;
        } else if (cmd == 6) {
            // back
            cout << "back" << endl;
        }
    }
    return 0;
}
