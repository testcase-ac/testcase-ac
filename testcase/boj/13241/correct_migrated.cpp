#include <iostream>
using namespace std;
int main() {
    long long a,b;
    cin >> a >> b;
    long long c=a,d=b;
    while(c!=d) {
        if(c>d) {
            c=c-d;
        } else {
            d=d-c;
        }
    } cout << a*b/c << endl;
}
