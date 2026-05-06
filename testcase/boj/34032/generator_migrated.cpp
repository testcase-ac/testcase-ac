#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]){
  registerGen(argc,argv,1);
  int N=rnd.next(2,500000);
  cout<<N<<'\n';
  while(N--){cout<<(rnd.next(0,1)?'O':'X');}
  return 0;
}
