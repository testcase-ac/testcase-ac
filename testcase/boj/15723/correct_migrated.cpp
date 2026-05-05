#include<iostream>
#include<string>
using namespace std;

int n, m;
const int SZ = 26;
bool adj[30][30];

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	while(n--){
		char a, b; string is;
		cin >> a >> is >> b;
		adj[a-'a'][b-'a'] = 1;
	}
	cin >> m;
	for(int k = 0; k < SZ; k++){
		for(int i = 0; i < SZ; i++){
			for(int j = 0; j < SZ; j++){
				adj[i][j] |= (adj[i][k]&adj[k][j]);
			}
		}
	}
	while(m--){
		char a, b; string is;
		cin >> a >> is >> b;
		cout << ((adj[a-'a'][b-'a'])?"T":"F") << '\n';
	}
}
