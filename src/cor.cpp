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


// [[Rcpp::export]]

NumericVector par_col_cors(NumericMatrix& X,
                           NumericMatrix& Y,
                           int threads = 1)
{
#ifdef _OPENMP
  if ( threads > 0 )
    omp_set_num_threads( threads );
#endif

  std::size_t I = X.nrow();
  std::size_t J = X.ncol();
  NumericVector cors(J);
  double xiyi = 0;
  double xi2 = 0;
  double yi2 = 0;
  double mean_x;
  double mean_y;

#pragma omp parallel for
  for (std::size_t j = 0; j < J; j++) {
    xiyi = 0;
    xi2 = 0;
    yi2 = 0;
    mean_x = mean(X(_,j));
    mean_y = mean(Y(_,j));
    for (std::size_t i = 0; i < I; i++) {
      xiyi += (X(i,j) - mean_x) * (Y(i,j) - mean_y);
      xi2 += std::pow(X(i,j) - mean_x,2);
      yi2 += std::pow(Y(i,j) - mean_y,2);
    }
    cors(j) = xiyi / (std::pow(xi2,0.5) * std::pow(yi2,0.5));
  }
  return(cors);
}

