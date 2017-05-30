// #include <Rcpp.h>
// using namespace Rcpp;
// // [[Rcpp::depends(RcppArmadillo)]]
// #include <armadillo>
//
// //' Singular Value Decomposition
// //'
// //' Calculate the singular value decomposition of a matrix
// //'
// //' @param x A numeric vector
// //' @param na_rm Does nothing at present.
// //' @param threads The number of threads to run calculation over
// //' @export
// // [[Rcpp::export]]
// Rcpp::List rcpp_svd(NumericMatrix& X) {
//   arma::mat M(X.begin(), X.nrow(), X.ncol(),false);
//   arma::mat U;
//   arma::vec d;
//   arma::mat V;
//   arma::svd(U, d, V, M);
//
//   return Rcpp::List::create(Rcpp::Named("d") = d,
//                             Rcpp::Named("U") = U,
//                             Rcpp::Named("V") = V);
// }

