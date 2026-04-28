use io::Write;
use std::{io, str};

pub struct UnsafeScanner<R> {
  reader: R,
  buf_str: Vec<u8>,
  buf_iter: str::SplitAsciiWhitespace<'static>,
}

impl<R: io::BufRead> UnsafeScanner<R> {
  pub fn new(reader: R) -> Self {
    Self {
      reader,
      buf_str: vec![],
      buf_iter: "".split_ascii_whitespace(),
    }
  }
  
  pub fn token<T: str::FromStr>(&mut self) -> T {
    loop {
      if let Some(token) = self.buf_iter.next() {
        return token.parse().ok().expect("Failed parse");
      }
      self.buf_str.clear();
      self.reader
          .read_until(b'\n', &mut self.buf_str)
          .expect("Failed read");
      self.buf_iter = unsafe {
        let slice = str::from_utf8_unchecked(&self.buf_str);
        std::mem::transmute(slice.split_ascii_whitespace())
      }
    }
  }
}

const INF: i32 = 0x3f3f3f3f;

fn solve_k1(n: usize, a: &Vec<(i32, i32)>) -> i32 {
  let mut ans = INF;
  for c1 in 0..n {
    let (c1x, c1y) = a[c1];

    let mut cur = 0;
    for i in 0..n {
      let (x, y) = a[i]; let mut val = INF;
      val = val.min((x - c1x).abs() + (y - c1y).abs());
      cur = cur.max(val);
    }
    ans = ans.min(cur);
  }
  ans
}

fn solve_k2(n: usize, a: &Vec<(i32, i32)>) -> i32 {
  let mut ans = INF;
  for c1 in 0..n { for c2 in c1 + 1..n {
    let (c1x, c1y) = a[c1]; let (c2x, c2y) = a[c2];

    let mut cur = 0;
    for i in 0..n {
      let (x, y) = a[i]; let mut val = INF;
      val = val.min((x - c1x).abs() + (y - c1y).abs());
      val = val.min((x - c2x).abs() + (y - c2y).abs());
      cur = cur.max(val);
    }
    ans = ans.min(cur);
  }}
  ans
}

fn solve_k3(n: usize, a: &Vec<(i32, i32)>) -> i32 {
  let mut ans = INF;
  for c1 in 0..n { for c2 in c1 + 1..n { for c3 in c2 + 1..n {
    let (c1x, c1y) = a[c1]; let (c2x, c2y) = a[c2]; let (c3x, c3y) = a[c3];

    let mut cur = 0;
    for i in 0..n {
      let (x, y) = a[i]; let mut val = INF;
      val = val.min((x - c1x).abs() + (y - c1y).abs());
      val = val.min((x - c2x).abs() + (y - c2y).abs());
      val = val.min((x - c3x).abs() + (y - c3y).abs());
      cur = cur.max(val);
    }
    ans = ans.min(cur);
  }}}
  ans
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, k) = (scan.token::<usize>(), scan.token::<usize>());
  let mut a = vec![];
  for _ in 0..n {
    let (x, y) = (scan.token::<i32>(), scan.token::<i32>());
    a.push((x, y));
  }

  let ans;
  if k == 1 { ans = solve_k1(n, &a); }
  else if k == 2 { ans = solve_k2(n, &a); }
  else { ans = solve_k3(n, &a); }

  writeln!(out, "{}", ans).ok();
}

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());
  let mut out = io::BufWriter::new(stdout.lock());

  let t = 1;
  // let t = scan.token::<usize>();
  for _ in 0..t {
    solve(&mut scan, &mut out);
  }
}
