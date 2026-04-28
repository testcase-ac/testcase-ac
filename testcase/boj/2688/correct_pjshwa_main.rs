use std::io;
use std::io::BufRead;

const YMAX: usize = 65;
const XMAX: usize = 10;

fn solve(n: usize) {
    let mut dp = vec![vec![0; XMAX]; YMAX];
        
    for i in 0..XMAX {
        dp[1][i] = 1;
    }

    for y in 2..=n {
        for x in 0..XMAX {                                
            let mut sum = 0u64;
            for k in x..XMAX {
                sum = sum + dp[y-1][k];
            }
            dp[y][x] = sum;
        }
    }


    let mut sum = 0u64;
    for i in 0..XMAX {
        sum = sum + dp[n][i];
    }    
    println!("{}", sum);
}

fn main() {

    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();       
    let t = lines.next().unwrap().unwrap().parse::<i32>().unwrap();
    for _ in 0..t {
        let n = lines.next().unwrap().unwrap().parse::<usize>().unwrap();
        solve(n);
    }            
    
}
