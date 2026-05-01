use std::io::*;

fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_ascii_whitespace();
    let mut next = || it.next().unwrap().parse().unwrap();
    let mut stdout = stdout().lock();
    for _ in 0..next() {
        let [n, pa, pb] = [next(), next(), next()];
        let (pa, pb) = if pa < pb { (pa, pb) } else { (pb, pa) };
        let mut v: Vec<usize> = (0..n).map(|_| next()).collect();
        v.sort();
        let (i, j) = (v.partition_point(|&x| x < pa.midpoint(pb)), v.partition_point(|&x| x <= pa.midpoint(pb)));

        let [mut sum_a, mut sum_b]: [usize; 2] = [v[..i].iter().map(|&x| x - pa).sum(), v[j..].iter().map(|&x| pb - x).sum()];
        for &x in &v[i..j] {
            if sum_a < sum_b { sum_a += x - pa; }
            else { sum_b += pb - x; }
        }
        writeln!(stdout, "{} {}", 2 * (sum_a + sum_b), 2 * sum_a.abs_diff(sum_b)).unwrap();
    }
}
