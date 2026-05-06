#include <iostream>
#include <random>
#include <ctime>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);
    uniform_int_distribution<> dis_type(1, 3);
    
    int count = 0;
    while (true) {
        int a = dis(gen);
        int b = dis(gen);
        int type = dis_type(gen);
        
        if (type == 1) {
            b = a * (dis(gen) % 10 + 1);
            if(b<10001&&a!=b) cout << a << " " << b << endl;
        } else if (type == 2) {
            a = b * (dis(gen) % 10 + 1);
            if(a<10001&&a!=b) cout << a << " " << b << endl;
        } else {
            while (a % b == 0 || b % a == 0) {
                a = dis(gen);
                b = dis(gen);
            } if(a!=b) cout << a << " " << b << endl;
        }

        count++;
        if (count > 10 && dis_type(gen) == 3) {
            cout << "0 0" << endl;
            break;
        }
    } return 0;
}
