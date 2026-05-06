#include <iostream>
#include <random>
#include <string>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,1000);
    uniform_int_distribution<int> char_dist(0,25);
    
    int length = dist(gen);
    string s = "";

    for (int i = 0; i < length; i++) {
        s += 'a' + char_dist(gen);
    }
    cout << s << endl;
}
