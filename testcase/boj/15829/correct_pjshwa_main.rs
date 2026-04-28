use std::io::{self, BufRead};

fn lpow(x: u64, y: u64, m: u64) -> u64 {
    let mut xx = x;
    let mut yy = y;
    let mut r = 1u64;
    xx %= m;
    while yy > 0 {
        if yy & 1 == 1 {
            r = (r * xx) % m;
        }
        xx = (xx * xx) % m;
        yy >>= 1;
    }
    return r;
}

fn main() {
    let stdin = io::stdin();
    let mut iter = stdin.lock().lines();
    let n = iter.next().unwrap().unwrap().parse::<usize>().unwrap();
    let line = iter.next().unwrap().unwrap();
    let line_bytes = line.as_bytes();

    let mut sum = 0u64;
    let m = 1234567891u64;
    for i in 0..n {
        sum = (sum + lpow(31, i as u64, m) * (line_bytes[i] as u64 - 96)) % m;
    }
    println!("{}", sum);
}
