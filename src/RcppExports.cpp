// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// par_cor_vecs
double par_cor_vecs(NumericVector& x, NumericVector& y, int threads);
RcppExport SEXP _paraR_par_cor_vecs(SEXP xSEXP, SEXP ySEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector& >::type x(xSEXP);
    Rcpp::traits::input_parameter< NumericVector& >::type y(ySEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(par_cor_vecs(x, y, threads));
    return rcpp_result_gen;
END_RCPP
}
// par_cor_matrix
NumericMatrix par_cor_matrix(NumericMatrix& X, int threads);
RcppExport SEXP _paraR_par_cor_matrix(SEXP XSEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix& >::type X(XSEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(par_cor_matrix(X, threads));
    return rcpp_result_gen;
END_RCPP
}
// par_col_cors
NumericVector par_col_cors(NumericMatrix& X, NumericMatrix& Y, int threads);
RcppExport SEXP _paraR_par_col_cors(SEXP XSEXP, SEXP YSEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix& >::type X(XSEXP);
    Rcpp::traits::input_parameter< NumericMatrix& >::type Y(YSEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(par_col_cors(X, Y, threads));
    return rcpp_result_gen;
END_RCPP
}
// par_dist
NumericMatrix par_dist(NumericMatrix mat);
RcppExport SEXP _paraR_par_dist(SEXP matSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type mat(matSEXP);
    rcpp_result_gen = Rcpp::wrap(par_dist(mat));
    return rcpp_result_gen;
END_RCPP
}
// Rcpp_as_numeric_matrix
NumericMatrix Rcpp_as_numeric_matrix(DataFrame x);
RcppExport SEXP _paraR_Rcpp_as_numeric_matrix(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< DataFrame >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(Rcpp_as_numeric_matrix(x));
    return rcpp_result_gen;
END_RCPP
}
// par_mean
double par_mean(const Rcpp::NumericVector& x, bool na_rm);
RcppExport SEXP _paraR_par_mean(SEXP xSEXP, SEXP na_rmSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type na_rm(na_rmSEXP);
    rcpp_result_gen = Rcpp::wrap(par_mean(x, na_rm));
    return rcpp_result_gen;
END_RCPP
}
// par_colMeans
NumericVector par_colMeans(const NumericMatrix& mat);
RcppExport SEXP _paraR_par_colMeans(SEXP matSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const NumericMatrix& >::type mat(matSEXP);
    rcpp_result_gen = Rcpp::wrap(par_colMeans(mat));
    return rcpp_result_gen;
END_RCPP
}
// par_rank
NumericVector par_rank(NumericVector& x, int threads);
RcppExport SEXP _paraR_par_rank(SEXP xSEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector& >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(par_rank(x, threads));
    return rcpp_result_gen;
END_RCPP
}
// par_sort
NumericVector par_sort(NumericVector& x);
RcppExport SEXP _paraR_par_sort(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(par_sort(x));
    return rcpp_result_gen;
END_RCPP
}
// par_sum
double par_sum(NumericVector& x, bool na_rm, int threads);
RcppExport SEXP _paraR_par_sum(SEXP xSEXP, SEXP na_rmSEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector& >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type na_rm(na_rmSEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(par_sum(x, na_rm, threads));
    return rcpp_result_gen;
END_RCPP
}
// par_sum2
double par_sum2(NumericVector& x, bool na_rm, int threads);
RcppExport SEXP _paraR_par_sum2(SEXP xSEXP, SEXP na_rmSEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector& >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type na_rm(na_rmSEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(par_sum2(x, na_rm, threads));
    return rcpp_result_gen;
END_RCPP
}
// par_colSums
NumericVector par_colSums(const NumericMatrix& mat);
RcppExport SEXP _paraR_par_colSums(SEXP matSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const NumericMatrix& >::type mat(matSEXP);
    rcpp_result_gen = Rcpp::wrap(par_colSums(mat));
    return rcpp_result_gen;
END_RCPP
}
// par_var
double par_var(NumericVector x, bool na_rm, int threads);
RcppExport SEXP _paraR_par_var(SEXP xSEXP, SEXP na_rmSEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type na_rm(na_rmSEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(par_var(x, na_rm, threads));
    return rcpp_result_gen;
END_RCPP
}
// par_colVars
NumericVector par_colVars(const NumericMatrix& x, bool na_rm, int threads);
RcppExport SEXP _paraR_par_colVars(SEXP xSEXP, SEXP na_rmSEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const NumericMatrix& >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type na_rm(na_rmSEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(par_colVars(x, na_rm, threads));
    return rcpp_result_gen;
END_RCPP
}

RcppExport SEXP _paraR_par_colSums2(SEXP, SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"_paraR_par_cor_vecs", (DL_FUNC) &_paraR_par_cor_vecs, 3},
    {"_paraR_par_cor_matrix", (DL_FUNC) &_paraR_par_cor_matrix, 2},
    {"_paraR_par_col_cors", (DL_FUNC) &_paraR_par_col_cors, 3},
    {"_paraR_par_dist", (DL_FUNC) &_paraR_par_dist, 1},
    {"_paraR_Rcpp_as_numeric_matrix", (DL_FUNC) &_paraR_Rcpp_as_numeric_matrix, 1},
    {"_paraR_par_mean", (DL_FUNC) &_paraR_par_mean, 2},
    {"_paraR_par_colMeans", (DL_FUNC) &_paraR_par_colMeans, 1},
    {"_paraR_par_rank", (DL_FUNC) &_paraR_par_rank, 2},
    {"_paraR_par_sort", (DL_FUNC) &_paraR_par_sort, 1},
    {"_paraR_par_sum", (DL_FUNC) &_paraR_par_sum, 3},
    {"_paraR_par_sum2", (DL_FUNC) &_paraR_par_sum2, 3},
    {"_paraR_par_colSums", (DL_FUNC) &_paraR_par_colSums, 1},
    {"_paraR_par_var", (DL_FUNC) &_paraR_par_var, 3},
    {"_paraR_par_colVars", (DL_FUNC) &_paraR_par_colVars, 3},
    {"_paraR_par_colSums2",           (DL_FUNC) &_paraR_par_colSums2,           4},
    {NULL, NULL, 0}
};

RcppExport void R_init_paraR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
