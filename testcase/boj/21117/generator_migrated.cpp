#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
	mt19937_64 g(rd());
	int n=g()%21+1; //n>=22이면 testcase.ac에서 짤림
	cout<<n<<'\n';
	for(int i=0;i<n*2;i++) {
	    for(int j=0;j<n;j++) cout<<g()%2;
	    cout<<'\n';
	}
}
