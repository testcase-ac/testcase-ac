#include <iostream>
#include <string>

using namespace std;

int main(){
	int n;
	while(true){
		cin >> n;
		if(n == 0) break;

		string s;
		cin >> s;
		int size = s.size();
		// cout << size;
		int breaks = size / n;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < breaks; j++){
				if(j % 2 == 0) cout << s[i + n * j];
				else cout << s[n * (j + 1) - i - 1];
			}
		}
		cout << endl;
	}
}