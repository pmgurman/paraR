#include <Rcpp.h>

using namespace Rcpp;
// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

#include <cmath>
#include <algorithm>

// helper function for taking the average of two numbers
inline double sq_diff(double val1, double val2) {
  return  std::pow(val1 - val2,2);
}


struct Distance : public Worker {

  // input matrix to read from
  const RMatrix<double> mat;

  // output matrix to write to
  RMatrix<double> rmat;

  // initialize from Rcpp input and output matrixes (the RMatrix class
  // can be automatically convelrted to from the Rcpp matrix type)
  Distance(const NumericMatrix mat, NumericMatrix rmat)
    : mat(mat), rmat(rmat) {}

  // function call operator that work for the specified range (begin/end)
  void operator()(std::size_t begin, std::size_t end) {
    for (std::size_t i = begin; i < end; i++) {
      for (std::size_t j = 0; j < i; j++) {

        // rows we will operate on
        RMatrix<double>::Row row1 = mat.row(i);
        RMatrix<double>::Row row2 = mat.row(j);

        // compute the average using std::tranform from the STL
        double diff_sum = 0;
#pragma omp simd reduction(+:diff_sum)
        for (std::size_t k = 0; k < row1.length(); k++) {
          diff_sum += std::pow(row1[k] - row2[k],2);
        }

        // write to output matrix
        rmat(i,j) = std::pow(diff_sum,0.5);
      }
    }
  }
};


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
NumericMatrix par_dist(NumericMatrix mat) {

  // allocate the matrix we will return
  NumericMatrix rmat(mat.nrow(), mat.nrow());

  // create the worker
  Distance distance(mat, rmat);

  // call it with parallelFor
  parallelFor(0, mat.nrow(), distance);

  return rmat;
}













