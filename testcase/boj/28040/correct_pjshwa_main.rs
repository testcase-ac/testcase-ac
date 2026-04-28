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

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  let mut adj = vec![vec![]; n + 1];
  let mut radj = vec![vec![]; n + 1];

  for i in 1..=n {
    let (u, v) = (scan.token::<usize>(), scan.token::<usize>());
    adj[i].push(u); adj[i].push(v);
    radj[u].push(i); radj[v].push(i);
  }

  for i in 1..=n {
    let mut avis = vec![true; n + 1];
    for sv in vec![adj[i][0], adj[i][1], i] {
      let mut cdist = vec![INF; n + 1];
      let mut q = std::collections::VecDeque::new();

      q.push_back(sv); cdist[sv] = 0;
      while let Some(u) = q.pop_front() {
        for &v in &radj[u] {
          if v == i { continue; }
          if cdist[v] == INF {
            cdist[v] = cdist[u] + 1;
            q.push_back(v);
          }
        }
      }

      for j in 1..=n {
        if cdist[j] == INF { avis[j] = false; }
      }
    }

    let mut f = false;
    for j in 1..=n { f |= avis[j]; }

    if f { write!(out, "Y").ok(); }
    else { write!(out, "N").ok(); }
  }
  writeln!(out).ok();
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
