#include <Rcpp.h>
#include <omp.h>
// [[Rcpp::plugins(openmp)]]
// [[Rcpp::depends(RcppProgress)]]
#include <progress.hpp>
using namespace Rcpp;
#include <parallel/numeric>


//' Vector and Matrix Sums
//'
//' Calculate the sum of a vector
//'
//' Calculate the sum of a numeric vector
//' OpenMP is used to calculate improve calculation times.
//' @param x A numeric vector
//' @param na_rm Does nothing at present.
//' @param threads The number of threads to run calculation over
//' @export
// [[Rcpp::export]]
double par_sum(NumericVector& x, bool na_rm = false, int threads = 1) {
#ifdef _OPENMP
  if ( threads > 0 )
    omp_set_num_threads( threads );
#endif
  int n = x.length();
  return(__gnu_parallel::accumulate(x.begin(), x.end(), 0.0));
}

//' Calculate the column sums for each column of a matrix.
//' OpenMP is used to calculate improve calculation times.
//' TODO: Needs to implement a multicore cliff.
//' @param x A numeric vector
//' @param na_rm Does nothing at present.
//' @param threads The number of threads to run calculation over
//' @export
// [[Rcpp::export]]
SEXP par_colSums(NumericMatrix& x, bool na_rm = false, int threads = 1, bool display_progress = false) {
#ifdef _OPENMP
  if ( threads > 0 )
    omp_set_num_threads( threads );
#endif

  int m = x.ncol();
  int n = x.nrow();
  NumericVector colSums(m);
  Progress p(n, display_progress);
#pragma omp parallel for schedule(dynamic)

    for (int j = 0; j < m; ++j) {
      if (! Progress::check_abort() ) {
        p.increment(); // update progress

        for (int i = 0; i < n; ++i) {
          colSums[j] += x(i,j);
        }
      }

    }


  return(colSums);
}

