#include "testlib.h"
using namespace std;
bool f[17][17];
vector<int> g[17];
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
    g[1]={2,3,4,5};
    g[6]={2,3,12,13};
    g[7]={2,4,12,14};
    g[8]={2,5,13,14};
    g[9]={3,4,12,15};
    g[10]={3,5,13,15};
    g[11]={4,5,14,15};
    g[16]={12,13,14,15};
	int n=rnd.next(0,32);
	cout<<n<<'\n';
	while(n--) {
	    int a,b;
	    while(1) {
	        a=rnd.next(1,15);
	        b=rnd.next(a+1,16);
            if(find(g[a].begin(),g[a].end(),b)==g[a].end()&&find(g[b].begin(),g[b].end(),a)==g[b].end()) continue;
	        if(!f[a][b]) break;
	    } cout<<a<<' '<<b<<'\n';
	    f[a][b]=1;
	}
}
