#include <Rcpp.h>
#include <omp.h>
using namespace Rcpp;
// [[Rcpp::plugins(openmp)]]


//' Calculate the varance of a vector.
//' Currently uses the Rcpp sugar implementation of the variance function.
//' TODO: Needs to implement a multicore cliff.
//' Based on https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
//' @param x A numeric vector
//' @export
// [[Rcpp::export]]
double par_var(NumericVector x, bool na_rm = false, int threads = 1)
{
#ifdef _OPENMP
  if ( threads > 0 )
    omp_set_num_threads( threads );
#endif

  std::size_t n = x.length();
  double sum1 = 0;
  double sum2 = 0;
#pragma omp parallel for reduction(+ : sum1)
  for (std::size_t i = 0; i < n; i++) {
    sum1 += x[i];
  }
  double mean = sum1 / n;

#pragma omp parallel for reduction(+ : sum2)
 for (int i = 0; i < n; i++) {
  sum2 += pow(x[i] - mean,2.0);
 }


  return(sum2 / (n - 1));
}

//' Calculate the column variances of a matrix
//' * OpenMP is used to calculate improve calculation times.
//' TODO: Needs to implement a multicore cliff.
//' @param x A numeric vector
//' @param na_rm Does nothing at present.
//' @param threads The number of threads to run calculation over
//' @export
// [[Rcpp::export]]
NumericVector par_colVars(const NumericMatrix& x, bool na_rm = false, int threads = 1) {
#ifdef _OPENMP
  if ( threads > 0 )
    omp_set_num_threads( threads );
#endif

  std::size_t I = x.nrow();
  std::size_t J = x.ncol();

  double sum1;
  double sum2;
  double mean;
  NumericVector variance = NumericVector(J);

#pragma omp parallel for
  for (std::size_t j = 0; j < J; j++){
    sum1=0;
    sum2=0;
    for (std::size_t i = 0; i < I; i++) {
      sum1 += x(i,j);
    }
    mean = sum1 / I;
    for (std::size_t i = 0; i < I; i++) {
      sum2 += pow(x(i,j) - mean, 2.0);
    }
    variance[j] = sum2 / (J - 1);
  }
  return(variance);
}
