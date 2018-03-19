//' @useDynLib paraR
//' @importFrom Rcpp sourceCpp


#include <Rcpp.h>
#include <parallel/algorithm>
using namespace Rcpp;
using namespace std;


//' * Sort a vector using __gnu_parallel::sort.
//' * Code is not parallel, but is more efficient for numeric vectors than base R.
//' Parallel sort codes is https://gcc.gnu.org/onlinedocs/libstdc++/manual/parallel_mode_using.html
//' @param x A numeric vector
//' @export
// [[Rcpp::export]]
NumericVector par_sort(NumericVector & x) {
  NumericVector sort_x = clone(x);
  copy(x.begin(),x.end(),sort_x.begin());
  __gnu_parallel::sort(sort_x.begin(), sort_x.end());
  return sort_x;
}




