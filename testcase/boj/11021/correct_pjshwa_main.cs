using System;
using System.Linq;

class Program {
    static void Main(){
        int n = int.Parse(Console.ReadLine());
        for(int i = 0; i < n; i++){
            int sum = Console.ReadLine().Split().Select(int.Parse).Sum();
            Console.WriteLine(string.Format("Case #{0}: {1}", i+1, sum));
        }
    }
}