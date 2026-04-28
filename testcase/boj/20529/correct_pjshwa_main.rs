use io::Write;
use std::{io, str, collections::HashMap};

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

fn pdist(a: &str, b: &str) -> usize {
  let mut cnt = 0;
  for i in 0..4 {
    if a.chars().nth(i) != b.chars().nth(i) {
      cnt += 1;
    }
  }
  cnt
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  let a = (0..n).map(|_| scan.token::<String>()).collect::<Vec<_>>();
  if n > 32 { writeln!(out, "0").ok(); return; }

  let mut ans = 0x3f3f3f3f;
  for i in 0..n { for j in i + 1..n { for k in j + 1..n {
    ans = ans.min(pdist(&a[i], &a[j]) + pdist(&a[j], &a[k]) + pdist(&a[k], &a[i]));
  }}}
  writeln!(out, "{}", ans).ok();
}

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());
  let mut out = io::BufWriter::new(stdout.lock());

  // let t = 1;
  let t = scan.token::<usize>();
  for _ in 0..t {
    solve(&mut scan, &mut out);
  }
}
