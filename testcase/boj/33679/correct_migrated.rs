use std::io::*;

fn main() {
    let input = read_to_string(stdin()).unwrap();
    let yjhg: Vec<_> = input.lines().skip(1).map(|s| lis(s.split_whitespace().flat_map(str::parse).collect())).collect();
    print!("{} Win!", if yjhg[0] > yjhg[1] { "YJ" } else if yjhg[0] < yjhg[1] { "HG" } else { "Both" });
}

fn lis(mut a: Vec<usize>) -> usize {
    let n = a.len();
    let mut max = 0;

    for _ in 0..n {
        let mut d = vec![0; n];
        let mut e = vec![];

        let (mut j, mut l) = (0, 0);

        for i in 0..n {
            d[i] = e.partition_point(|&e| e < a[i]);

            if d[i] < e.len() { e[d[i]] = a[i]; }
            else { e.push(a[i]); }

            if l < d[i] { (j, l) = (i, d[i]); }
        }

        let mut cnt = 1;

        for i in (0..j).rev() {
            if a[i] < a[j] && d[i] + 1 == l {
                l -= 1;
                j = i;
                cnt += 1;
            }
        }

        max = max.max(cnt);

        a.rotate_left(1);
    }

    max
}
