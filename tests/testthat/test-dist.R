context("test-dist.R")

# Should test that all examples from ?dist work

test_that("dist matrix works", {
  x <- matrix(rnorm(100), nrow = 5)
  expect_equivalent(dist(x), as.dist(par_dist(x)))
})
