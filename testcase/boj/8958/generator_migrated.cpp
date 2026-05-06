#include <iostream>
#include <random>
#include <string>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 1);
    uniform_int_distribution<int> ran(1, 40);
    uniform_int_distribution<int> dis(1, 10);
    int t=dis(gen);
    cout<<t<<"\n";
    for (int i = 0; i < t; i++) {
        int len = ran(gen);
        string result;
        for (int j = 0; j < len; j++) {
            result += dist(gen) == 0 ? 'X' : 'O';
        }
        cout << result << endl;
    }
    return 0;
}
