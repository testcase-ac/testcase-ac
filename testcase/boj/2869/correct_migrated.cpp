#include <iostream>
using namespace std;

int main() {
    int a,b,c;
    cin >> a >> b >> c;
    if((c-b)%(a-b)==0) {
        cout << int((c-b)/(a-b));
    } else {
        cout << int((c-b)/(a-b))+1;
    }
}
