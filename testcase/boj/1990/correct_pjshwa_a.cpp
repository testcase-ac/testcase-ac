//
//  main.cpp
//  1990
//
//  Created by Hyun-sung Kim on 05/01/2019.
//  Copyright © 2019 Hyun-sung Kim. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;

bool isItPrime( int n ){
    for( int i = 2; i <= sqrt(n); i++ )
        if( n%i == 0 ) return false;
    return true;
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int M, N;
    string HT = "1379";
    cin >> M >> N;
    
    string start = to_string(M), end = to_string(N);
    
    for( long i = start.length(); i <= end.length(); i++ ){
        if( i == 1 )
        {
            for( int j = M; j < 10; j++ )
                if( isItPrime(j) ) cout << j << "\n";
        }
        
        else if( i > 2 && i%2 == 0 ) continue;
        
        else
        {
            string palindrome;
            for( int j = 0; j < i; j++ ) palindrome += "0";
            
            for( int k = 0; k < 4; k++ ){
                palindrome[0] = palindrome[i-1] = HT[k];
                for( int l = 0; l < pow( 10, (i-1)/2 ); l++ ){
                    int temp = l;
                    for( long m = (i-1)/2 ; m > 0; m-- ){
                        palindrome[m] = palindrome[i-1-m] = (char)(temp%10+'0');
                        temp /= 10;
                    }
                    if( stoi(palindrome) > N ){
                        cout << -1;
                        return 0;
                    }
                    if( isItPrime(stoi(palindrome)) && stoi(palindrome) >= M )
                        cout << palindrome << "\n";
                }
            }
        }
    }

    cout << -1;
    return 0;
}
