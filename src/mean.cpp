#include <Rcpp.h>
using namespace Rcpp;

#include <omp.h>
// [[Rcpp::plugins(openmp)]]

#include <parallel/numeric>

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

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
#pragma omp  simd reduction(+:value)

     for (int i = begin; i < end; ++i) {
       value += input[i];
     }

   }

  // join my value with that of another Sum
  void join(const Sum& rhs) {
    value += rhs.value;
  }
};



struct ColMeans : public Worker {

  // input matrix to read from
  const RMatrix<double> mat;

  // output matrix to write to
  RVector<double> rvec;

  // initialize from Rcpp input and output matrixes (the RMatrix class
  // can be automatically converted to from the Rcpp matrix type)
  ColMeans(const NumericMatrix mat, NumericVector rvec)
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


//' Calculate the mean of a numeric vector
//' OpenMP is used to calculate improve calculation times.
//' @param x A numeric vector
//' @param na_rm Does nothing at present.
//' @param threads The number of threads to run calculation over
//' @export
// [[Rcpp::export]]
double par_mean(const Rcpp::NumericVector& x, bool na_rm = false) {

  // declare the Sum instance
  Sum sum(x);

  // call parallel_reduce to start the work
  parallelReduce(0, x.length(), sum, 1000);

  // return the computed sum
  return sum.value / x.length();
}



//' Calculate the column means for each column of a matrix.
//' OpenMP is used to calculate improve calculation times.
//' TODO: Needs to implement a multicore cliff.
//' @param x A numeric vector
//' @param na_rm Does nothing at present.
//' @param threads The number of threads to run calculation over
//' @export
// [[Rcpp::export]]
NumericVector par_colMeans(const NumericMatrix& mat) {

  // allocate the matrix we will return
  NumericVector rvec(mat.ncol());

  // create the worker
  ColMeans colMeans(mat, rvec);

  // call it with parallelFor
  parallelFor(0, mat.nrow(), colMeans); //, 10

  return rvec;
}









