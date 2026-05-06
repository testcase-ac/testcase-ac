#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int r[3];
    while(1) {
        cin >> r[0] >> r[1] >> r[2];
        sort(r,r+3);
        if(r[0]==0) {
            return 0;
        }
        if(r[2]>=r[0]+r[1]) {
            cout << "Invalid" << endl;
        } else if(r[0]==r[1] && r[1]==r[2] && r[0]==r[2]) {
            cout << "Equilateral" << endl;
        } else if(r[0]==r[1] || r[1]==r[2] || r[0]==r[2]) {
            cout << "Isosceles" << endl;
        } else {
            cout << "Scalene" << endl;
        }
    }
}
