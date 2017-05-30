#include <Rcpp.h>
#include <omp.h>
// [[Rcpp::plugins(openmp)]]
// [[Rcpp::depends(RcppProgress)]]
#include <progress.hpp>
using namespace Rcpp;

//' Matrix Distance Measures
//'
//' Calculate the distance bewteen matrix rows using various distance measures.
//'
//' OpenMP is used to calculate improve calculation times.
//' @param x A numeric vector
//' @param na_rm Does nothing at present.
//' @param threads The number of threads to run calculation over
//' @export
// [[Rcpp::export]]
SEXP rcpp_dist(NumericMatrix& x, std::string method = "euclidian",
                        bool na_rm = false, int threads = 1, bool display_progress = false) {
  int x_nrows = x.nrow();
  int x_ncols = x.ncol();
  NumericMatrix dist(x_nrows,x_nrows);

#ifdef _OPENMP
    omp_set_num_threads(threads);
#endif


 Progress p(x_nrows, display_progress);
#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < x_nrows; ++i) {
    if (!Progress::check_abort() ) {
      for (int j = 0; j<=i; ++j) {
        if (method == "euclidian") {
          double temp_dist = 0;

          for (int k = 0; k< x_ncols; k++) {
            temp_dist += pow(x(i,k) - x(j,k),2);
          }
          dist(i,j) = pow(temp_dist,0.5);
        } else if (method == "hamming") {

          double temp_dist = 0;

          for (int k = 0; k < x_ncols; k++) {
            if (x(i,k) != x(j,k)) {
              temp_dist += 1;
            }
          }
          dist(i,j) = temp_dist / x_ncols;
        }
      }
    }
    p.increment();
  }
  return(dist);
}



