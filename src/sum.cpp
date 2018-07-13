#include <Rcpp.h>
using namespace Rcpp;

#include <omp.h>
// [[Rcpp::plugins(openmp)]]

#include <parallel/numeric>

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;






struct ColSums : public Worker {

  // input matrix to read from
  const RMatrix<double> mat;

  // output matrix to write to
  RVector<double> rvec;

  // initialize from Rcpp input and output matrixes (the RMatrix class
  // can be automatically converted to from the Rcpp matrix type)
  ColSums(const NumericMatrix mat, NumericVector rvec)
    : mat(mat), rvec(rvec) {}

  // function call operator that work for the specified range (begin/end)
  void operator()(std::size_t begin, std::size_t end) {
    for (std::size_t j = begin; j < end; j++) {

      // rows we will operate on
      RMatrix<double>::Column col = mat.column(j);

      // write to output matrix
      double value = 0;
#pragma omp  simd reduction(+:value)

      for (int i = 0; i < col.length(); ++i) {
        value += col[i];
      }

      rvec[j] = value;

      //rvec[j] = std::accumulate(col.begin(), col.end(), 0.0) / col.length();
    }
  }
};



//' Calculate the column sums for each column of a matrix.
//' OpenMP is used to calculate improve calculation times.
//' TODO: Needs to implement a multicore cliff.
//' @param x A numeric vector
//' @param na_rm Does nothing at present.
//' @param threads The number of threads to run calculation over
//' @export
// [[Rcpp::export]]
NumericVector par_colSums(const NumericMatrix& mat) {

  // allocate the matrix we will return
  NumericVector rvec(mat.ncol());

  // create the worker
  ColSums colSums(mat, rvec);

  // call it with parallelFor
  parallelFor(0, mat.nrow(), colSums);

  return rvec;
}
