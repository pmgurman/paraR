
#' Correlation using OpenMP
#'
#' @param x A numeric vector
#' @param y A nueric vector
#' @param use Not Implemented
#' @param method Method for calcuating the correlation. Curreltly supports Pearson and Spearman correlations.
#' @param threads Threads to use for OpenMP
#'
#' @return
#' @export
#'
#' @examples
par_cor <- function(x, y = NULL, use = "everything", method = "pearson", threads = 1L) {

  if (is.vector(x) & is.vector(y)) {
    if (method == "spearman") {
      x_rank <- par_rank(x,threads = threads)
      y_rank <- par_rank(y,threads = threads)
      par_cor_vecs(x_rank,y_rank,threads = threads)
    } else {
      par_cor_vecs(x,y,threads)
    }
  } else if(is.matrix(x)  & is.null(y)) {
    if (method == "spearman") {
      stop("Spearman is not currently supported on a matrix")
    } else {
      # par_cor_matrix(x,threads = threads)
    }
  }



}
