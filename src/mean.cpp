#include <Rcpp.h>
#include <omp.h>
// [[Rcpp::plugins(openmp)]]
// [[Rcpp::depends(RcppProgress)]]
#include <progress.hpp>
using namespace Rcpp;
#include <parallel/numeric>


//' Calculate the mean of a numeric vector
//' OpenMP is used to calculate improve calculation times.
//' @param x A numeric vector
//' @param na_rm Does nothing at present.
//' @param threads The number of threads to run calculation over
//' @export
// [[Rcpp::export]]
double par_mean(NumericVector& x, bool na_rm = false, int threads = 1) {
#ifdef _OPENMP
  if ( threads > 0 )
    omp_set_num_threads( threads );
#endif

  double mean = __gnu_parallel::accumulate(x.begin(), x.end(), 0.0);
return(mean / x.length());
}

// [[Rcpp::depends(RcppProgress)]]
#include <progress.hpp>

//' Calculate the column means for each column of a matrix.
//' OpenMP is used to calculate improve calculation times.
//' TODO: Needs to implement a multicore cliff.
//' @param x A numeric vector
//' @param na_rm Does nothing at present.
//' @param threads The number of threads to run calculation over
//' @export
// [[Rcpp::export]]
NumericVector par_colMeans(NumericMatrix& x, bool na_rm = false, int threads = 1, bool display_progress = false) {
#ifdef _OPENMP
  if ( threads > 0 )
    omp_set_num_threads( threads );
#endif

  int m = x.ncol();
  int n = x.nrow();
  NumericVector colMeans(m);
#pragma omp parallel for
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      colMeans[j] += x(i,j);
    }
  }
  return(colMeans / n);
}
