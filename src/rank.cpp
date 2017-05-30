#include <Rcpp.h>
#include <omp.h>
#include <parallel/algorithm>
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::plugins(openmp)]]


// Code based on with parallelisation where possible
// http://stackoverflow.com/questions/30822729/create-ranking-for-vector-of-double/30827731#30827731
// [[Rcpp::export]]
NumericVector par_rank(NumericVector & x, int threads = 1) {
#ifdef _OPENMP
  if ( threads > 0 )
    omp_set_num_threads( threads );
#endif

  std::vector<std::size_t> w(x.size());
  std::iota(begin(w), end(w), 0);
  __gnu_parallel::sort(begin(w), end(w),
            [&x](std::size_t i, std::size_t j) { return x[i] < x[j]; });

  NumericVector r(w.size());
  std::size_t n = 1;
#pragma omp parallel for
  for (std::size_t i = 0; i < w.size(); i += n)
  {

    while (i + n < w.size() && x[w[i]] == x[w[i+n]]) ++n;
    for (std::size_t k = 0; k < n; ++k)
    {
      r[w[i + k]] = i + (n + 1) / 2.0; // average rank of n tied values
      // r[w[i + k]] = i + 1;          // min
      // r[w[i + k]] = i + n;          // max
      // r[w[i + k]] = i + k + 1;      // random order
    }
  }
  return r;
}
