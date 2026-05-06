#include <iostream>
using namespace std; 
int main() 
{ 
    long long n; 
    cin >> n;
    n=n%7; 
    if (n==2 || n==0) {
        cout << "CY"; 
    } else {
        cout << "SK"; 
    }
}
