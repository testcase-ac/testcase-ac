use std::io::*;

fn main() {
    let input = read_to_string(stdin()).unwrap();
    let mut it = input.lines();
    let x = it.next().unwrap().parse().unwrap();
    let mut q: Vec<_> = it.next().unwrap().chars().map(|c| if c == 'M' { 1 } else { -1 }).collect();

    let [mut diff, mut cnt] = [0i32; 2];

    while !q.is_empty() {
        if (diff + q[0]).abs() <= x {
            diff += q[0];
            cnt += 1;
            q.remove(0);
        } else if q.len() > 1 && (diff + q[1]).abs() <= x {
            diff += q[1];
            cnt += 1;
            q.remove(1);
        } else { break; }
    }

    print!("{cnt}");
}
