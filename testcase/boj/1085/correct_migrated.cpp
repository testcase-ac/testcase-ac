#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int x,y,z,w,s;
    cin >> x >> y >> z >> w;
    cout<<min(min(x,z-x),min(y,w-y));
}
