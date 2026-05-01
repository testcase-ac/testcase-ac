use std::io::*;

fn main() {
    let input = read_to_string(stdin()).unwrap();
    let mut it = input.split_whitespace().flat_map(str::parse);
    let mut x = || it.next().unwrap();
    let mut out = BufWriter::new(stdout().lock());

    let [n, q] = [(); 2].map(|_| x() as usize);
    let a: Vec<i64> = (0..n).map(|_| x()).collect();

    let mut d: Vec<i64> = (0..n).map(|i| if i == 0 { 0 } else { a[i] - a[i - 1] }).collect();
    let mut neg = d.iter().filter(|&&v| v < 0).count();

    macro_rules! update {
        ($i: expr, $v: expr) => {
            if d[$i] < 0 && d[$i] + $v >= 0 { neg -= 1; }
            if d[$i] >= 0 && d[$i] + $v < 0 { neg += 1; }
            d[$i] += $v;
        };
    }

    for _ in 0..q {
        if x() == 1 {
            let (i, j, v) = (x() as usize - 1, x() as usize, x());
            if i > 0 { update!(i, v); }
            if j < n { update!(j, -v); }
        } else {
            writeln!(out, "{}", if neg > 0 { "NO" } else { "YES" }).ok();
        }
    }
}
