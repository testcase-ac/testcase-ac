#include <iostream>
using namespace std;

int main() {
    int a;
    while(1) {
        cin >> a;
        if(a==-1) {
            break;
        } else if(a==6) {
            cout << "6 = 1 + 2 + 3" << endl;
        } else if(a==28) {
            cout << "28 = 1 + 2 + 4 + 7 + 14" << endl;
        } else if(a==496) {
            cout << "496 = 1 + 2 + 4 + 8 + 16 + 31 + 62 + 124 + 248" << endl;
        } else if(a==8128) {
            cout << "8128 = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 127 + 254 + 508 + 1016 + 2032 + 4064" << endl;
        } else {
            cout << a << " is NOT perfect." << endl;
        }
    }
}
