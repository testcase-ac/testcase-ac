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
  let (n, m) = (scan.token::<usize>(), scan.token::<usize>());

  let mut adj = vec![vec![]; n + 1];
  let mut indegree = vec![0; n + 1];
  for _ in 0..m {
    let (u, v) = (scan.token::<usize>(), scan.token::<usize>());
    adj[u].push(v); indegree[v] += 1;
  }

  let mut w = vec![0.0; n + 1]; w[1] = 100.0;

  let mut q = std::collections::VecDeque::new();
  for i in 1..=n {
    if indegree[i] == 0 { q.push_back(i); }
  }

  while let Some(u) = q.pop_front() {
    let z = adj[u].len();
    if z == 0 { continue; }

    for &v in &adj[u] {
      w[v] += w[u] / z as f64;
      indegree[v] -= 1;
      if indegree[v] == 0 { q.push_back(v); }
    }
  }

  let mut ans: f64 = 0.0;
  for i in 1..=n {
    if adj[i].len() == 0 { ans = ans.max(w[i]); }
  }
  writeln!(out, "{:.10}", ans).ok();
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
