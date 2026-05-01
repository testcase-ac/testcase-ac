use std::io::*;

fn main() {
    let input = read_to_string(stdin()).unwrap();

    let (mut l, mut r) = (i64::MIN, i64::MAX);

    for mut x in input.lines().skip(1).map(|s| s.split_whitespace().flat_map(str::parse::<i64>)) {
        let (a, rhs) = (x.next().unwrap(), -x.next().unwrap() + x.next().unwrap());
        if a > 0 {
            r = r.min(if rhs >= 0 { rhs / a } else {(rhs + 1) / a - 1});
        } else {
            let (a, rhs) = (-a, -rhs);
            l = l.max(if rhs <= 0 { rhs / a } else {(rhs - 1) / a + 1});
        }
    }

    print!("{}", if l == i64::MIN || r == i64::MAX { -1 } else if r < l { 0 } else { r - l + 1});
}
