using System;

class P {
    static void Main(){
        int n = int.Parse(Console.ReadLine());
        for(int i = 0; i < 2*n-1; i++){
            if(n>i) Console.WriteLine(new String('*', i+1));
            else Console.WriteLine(new String('*', 2*n-i-1));
        }
    }
}