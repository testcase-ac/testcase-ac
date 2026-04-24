#include <iostream>
using namespace std;

int main ()
{
	int num_of_0[41];
	int num_of_1[41];
	num_of_0[0] = num_of_1[1] = 1;
	num_of_0[1] = num_of_1[0] = 0;
	for(int i=2; i<=40; i++) {
		num_of_0[i] = num_of_0[i-2] + num_of_0[i-1];
		num_of_1[i] = num_of_1[i-2] + num_of_1[i-1];
	}
	int T;
	cin >> T;
	int n;
	for(int i=0;i<T;i++) {
		cin >> n;
		cout << num_of_0[n] << ' ' << num_of_1[n] << '\n'; 
	}
}
