#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

// We can now use the BH package
// [[Rcpp::depends(BH)]]
struct Sum : public Worker
{
  // source vector
  const RVector<double> input;

  // accumulated value
  double value;

  // constructors
  Sum(const NumericVector input) : input(input), value(0) {}
  Sum(const Sum& sum, Split) : input(sum.input), value(0) {}

  // accumulate just the element of the range I've been asked to
  void operator()(std::size_t begin, std::size_t end) {
    value += std::accumulate(input.begin() + begin, input.begin() + end, 0.0);
  }

  // join my value with that of another Sum
  void join(const Sum& rhs) {
    value += rhs.value;
  }
};
//
// //' Calculate the mean of a numeric vector
// //' OpenMP is used to calculate improve calculation times.
// //' @param x A numeric vector
// //' @param na_rm Does nothing at present.
// //' @param threads The number of threads to run calculation over
// //' @export
// // [[Rcpp::export]]
// double par_mean(Rcpp::NumericVector& x, bool na_rm = false) {
//
//   // declare the Sum instance
//   Sum sum(x);
//
//   // call parallel_reduce to start the work
//   parallelReduce(0, x.length(), sum, 1000);
//
//   // return the computed sum
//   return sum.value / x.length();
// }
