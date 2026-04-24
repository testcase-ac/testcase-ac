#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
#define DIGITCNT 10
const int MAXNODE = 10000 * DIGITCNT;
int trie[MAXNODE][DIGITCNT];
bool isend[MAXNODE];

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		set0(trie);
		set0(isend);
		int n;
		bool ans = true;
		cin >> n;
		int next = 1;
		while(n--) {
			string str;
			cin >> str;
			if(!ans) continue;
			int t = 0;
			bool allexist = true;
			for(int i=0; i<sz(str); i++) {
				int c = str[i] - '0';
				if(trie[t][c] == 0) {  // create node
					if(allexist && isend[t]) {
						ans = false;
						//printf("ans=false: added is longer\n");
					}
					trie[t][c] = next;
					t = next;
					next++;
					allexist = false;
				} else { // use existing node
					t = trie[t][c];
				}
			}
			isend[t] = true;
			if(allexist) { // is a prefix of existing string
				ans = false;
				//printf("ans=false: added is shorter\n");
			}

		}
		cout << (ans ? "YES\n" : "NO\n");
	}
}
