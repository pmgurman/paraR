// #include <Rcpp.h>
// #include <R_ext/Lapack.h>
// #include <R_ext/BLAS.h>
//
// //[[Rcpp::export]]
// Rcpp::NumericMatrix QRopenblas(Rcpp::NumericMatrix X)
// {
//   // Declare variables
//   int n_rows = X.nrow(), n_cols = X.ncol(), min_mn = std::min(n_rows, n_cols);
//   Rcpp::NumericVector tau(min_mn);
//
//   // Perform QR decomposition
//   LAPACKE_dgeqrf(CblasColMajor, n_rows, n_cols, X.begin(), n_rows, tau.begin());
//
//   return X;
// }
