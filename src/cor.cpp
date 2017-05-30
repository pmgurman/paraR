#include <Rcpp.h>
#include <omp.h>
using namespace Rcpp;

// [[Rcpp::plugins(openmp)]]


// [[Rcpp::export]]
double par_cor_vecs(NumericVector& x,
                     NumericVector& y,
                     int threads = 1)
{
#ifdef _OPENMP
  if ( threads > 0 )
    omp_set_num_threads( threads );
#endif

  double mean_x = mean(x);
  double mean_y = mean(y);
  int n = x.length();
  double xiyi = 0;
  double xi2 = 0;
  double yi2 = 0;



#pragma omp parallel for reduction(+ : xiyi,xi2,yi2)
  for (int i = 0; i < n;i++)
  {
    xiyi += (x[i] - mean_x) * (y[i] - mean_y);
    xi2 += std::pow(x[i]- mean_x,2);
    yi2 += std::pow(y[i]- mean_y,2);
  }

  return(xiyi / (std::pow(xi2,0.5) * std::pow(yi2,0.5)));
}

// [[Rcpp::export]]
NumericMatrix par_cor_matrix(NumericMatrix& X,
                              int threads = 1)
{
#ifdef _OPENMP
  if ( threads > 0 )
    omp_set_num_threads( threads );
#endif

  int N = X.nrow();
  int I = X.ncol();
  int J = X.ncol();
  double xi12 = 0;
  double xi1 = 0;
  double xi2 = 0;
  double mean_x1;
  double mean_x2;

  NumericMatrix cormat(I,J);

#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < I; i++) {
    for (int j = 0; j < J; j++) {

      xi12 = 0;
      xi1 = 0;
      xi2 = 0;
      mean_x1 = mean(X(_,i));
      mean_x2 = mean(X(_,j));

      for (int n = 0; n < N;n++)
      {
        xi12 += (X(n,i) - mean_x1) * (X(n,j) - mean_x2);
        xi1 += std::pow(X(n,i) - mean_x1,2);
        xi2 += std::pow(X(n,j) - mean_x2,2);

      }
      cormat(i,j) = xi12 / (std::pow(xi1,0.5) * std::pow(xi2,0.5));
    }
  }
  return(cormat);
}


////' Calculate the mean of a numeric vector
////' OpenMP is used to calculate improve calculation times.
////' @param x A numeric vector
////' @param na_rm Does nothing at present.
////' @param threads The number of threads to run calculation over
////' @export
// // [[Rcpp::export]]
//
// NumericVector par_col_cors(NumericMatrix& x,
//                            NumericMatrix& y,
//                            int threads = 1)
// {
// #ifdef _OPENMP
//   if ( threads > 0 )
//     omp_set_num_threads( threads );
// #endif
//
//   std::size_t I = x.nrow();
//   std::size_t J = x.ncol();
//   NumericVector cors(J);
// #pragma omp parallel for
// for (std::size_t j; j <= J; j++) {
//   for (std::size_t i; i <= I; i++) {
//
//   }
// }
//
// return(cors);
// }

