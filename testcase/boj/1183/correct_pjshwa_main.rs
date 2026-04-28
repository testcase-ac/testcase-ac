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

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  let a = (0..n).map(|_| (scan.token::<i32>(), scan.token::<i32>())).collect::<Vec<_>>();

  let mut v = vec![];
  for (x, y) in &a { v.push(y - x); }
  v.sort();

  let mut s = vec![];
  for e in &v {
    let mut cur: i64 = 0;
    for (x, y) in &a {
      cur += (x + e - y).abs() as i64;
    }
    s.push(cur);
  }

  let mmin = s.iter().min().unwrap();
  let mut ans: i32 = 0;
  for i in 0..n {
    if s[i] == *mmin {
      ans += 1;
      if i > 0 && s[i - 1] == *mmin {
        ans += v[i] - v[i - 1] - 1;
      }
    }
  }
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
