using System;
 
public class Program {
    public static void Main() {
        string[] s = Console.ReadLine().Split();
        int n = int.Parse(s[0]); int m = int.Parse(s[1]);
        int[,] array = new int[n, m];
        for(int i = 0; i < n; i++){
            string[] nrow = Console.ReadLine().Split();
            for(int j = 0; j < m; j++){
                array[i,j] = int.Parse(nrow[j]);
            }
        }
        int k = int.Parse(Console.ReadLine());
        int ii, jj, x, y, sum;
        for(int p = 0; p < k; p++){
            string[] ijxy = Console.ReadLine().Split();
            sum = 0;
            ii = int.Parse(ijxy[0]);
            jj = int.Parse(ijxy[1]);
            x = int.Parse(ijxy[2]);
            y = int.Parse(ijxy[3]);
            for(int i = ii - 1; i < x; i++){
                for(int j = jj - 1; j < y; j++){
                    sum += array[i, j];
                }
            }
            Console.WriteLine(sum);
        }
        
        
    }
}