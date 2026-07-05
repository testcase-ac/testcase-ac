#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int N=rnd.next(1,1000000);
	int M=rnd.next(1,1000000);
	vector<int> divisors;
	for(int d=1;1LL*d*d<=N;d++){
		if(N%d==0){
			divisors.push_back(d);
			if(d!=N/d) divisors.push_back(N/d);
		}
	}
	int K=divisors[rnd.next((int)divisors.size())];
	cout<<N<<' '<<M<<' '<<K<<'\n';
}
