using System;
using System.Linq;
using System.Collections.Generic;
using System.Threading.Tasks;

// sums using parallel foreach
class P{
    int[] answers;
    void Run(){
        int n = int.Parse(Console.ReadLine());
        answers = new int[n];
        var args = new List<List<int>>();
        for(int i = 0; i < n; i++){
        	args.Add(new List<int>(Console.ReadLine().Split().Select(int.Parse)));
        }
        Parallel.ForEach(Enumerable.Range(0,n), (i) => {
        	answers[i] = args[i].Sum();
        });
        foreach(var answer in answers){
        	Console.WriteLine(answer);
        }
    }
    static void Main(String[] args){
        new P().Run();
    }
}