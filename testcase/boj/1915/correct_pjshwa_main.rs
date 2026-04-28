use std::io;
use std::io::BufRead;
use std::cmp;

const CHARNUM: u8 = 48;

fn main() {
    
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();    
    let (n,m) = {
        let l = lines.next();
        let l2 = l.unwrap().unwrap();
        let mut iter = l2.split_whitespace();
        (iter.next().unwrap().parse::<usize>().unwrap(), iter.next().unwrap().parse::<usize>().unwrap())
    };
    
    let mut grid = vec![vec![0 as i32; m+1]; n+1];
    let mut inp = String::new();

    for y in 1..=n {
        inp.clear();
        let v = lines.next();
        let vv = { 
            inp = v.unwrap().unwrap();
            inp.bytes() 
        };
        for (i,v1) in vv.enumerate() {
            grid[y][i+1] = (v1 - CHARNUM) as i32;
        }    
    }    

    let mut max_res = 0;

    for y in 1..n {
        for x in 1..m {
            let v = grid[y][x];
            if v == 0 || grid[y+1][x+1] == 0 {
                continue;
            }            
            grid[y+1][x+1] = grid[y+1][x+1] + cmp::min(cmp::min(grid[y][x], grid[y][x+1]), grid[y+1][x]);
        }
    }

    for y in 1..=n {
        for x in 1..=m {
            if max_res < grid[y][x] {
                max_res = grid[y][x];
            }
        }
    }

    println!("{}", max_res*max_res);
}
