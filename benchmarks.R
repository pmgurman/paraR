library(microbenchmark)
library(matrixStats)
library(rbenchmark)
library(OMPutils)
library(ggplot2)
library(parallel)

n <- 1E8
x <- rnorm(n, mean = 1E6, sd = 1E3)
X <- matrix(x,nrow = sqrt(n))
y <- rnorm(n)


# Sum ----
sum(x) - par_sum(x)
p <- microbenchmark(par_sum(x),
               par_sum(x, threads = 2),
               par_sum(x, threads = 4),
               sum(x))
p
autoplot(p)



summary(par_colSums(X) - colSums(X))
p <- microbenchmark(OMPutils:::par_colSums(X),
                    OMPutils:::par_colSums(X, threads = 2),
                    OMPutils:::par_colSums(X, threads = 4),
                    colSums(X),
                    colSums2(X))

p
autoplot(p)


# Mean ----

mean(x) - par_mean(x)
p <-microbenchmark(par_mean(x),
                   par_mean(x, threads = 2),
                   par_mean(x, threads = 4),
                   mean(x))
print(p)
autoplot(p)

colMeans(X) - par_colMeans(X)
p <-microbenchmark(par_colMeans(X),
                   OMPutils:::par_colMeans(X, threads = 2),
                   OMPutils:::par_colMeans(X, threads = 4),
                   mean(X))
print(p)
autoplot(p)



# Var -----

var(x) - par_var(x)
p <- microbenchmark(var(x),
                    par_var(x),
                    par_var(x,threads = 2),
                    par_var(x,threads = 4),
                    par_var(x,threads = 8))

print(p)
autoplot(p)

summary(colVars(X) - OMPutils:::par_colVars(X, threads = 4))
p <- microbenchmark(
                    matrixStats::colVars(X),
                      OMPutils:::par_colVars(X),
                      OMPutils:::par_colVars(X, threads = 2),
                      OMPutils:::par_colVars(X, threads = 4))

print(p)
autoplot(p)
# Cor ----

cor(x,y)  - par_cor(x,y)
p <- microbenchmark(cor(x,y),
               par_cor(x,y),
               par_cor(x,y,threads = 4))
print(p)
autoplot(p)


p <- microbenchmark(cor(x,y,method = "spearman"),
               par_cor(x,y,method = "spearman"),
               par_cor(x,y,threads = 4,method = "spearman"), times = 1)
print(p)
autoplot(p)

cor(x,y,method = "spearman") - par_cor(x,y,method = "spearman")

summary(as.numeric(cor(X) - par_cor(X)))

p <- microbenchmark(cor(X),
                      OMPutils:::par_cor(X),
                      OMPutils:::par_cor(X, threads = 4))


# Dist -----
X <- matrix(sample(0:2,5e5,replace = TRUE),nrow = 1e3)

system.time(par_dist(X,threads = 1))
system.time(par_dist(X,threads = 4))
system.time(dist(X))

test <- par_dist(X,method = 'hamming',parallel = T)
microbenchmark::microbenchmark(dist(X),rcpp_dist(X,threads = 1),rcpp_dist(X,threads = 8),times = 10)

# Sort ----
identical(sort(x),par_sort(x))
identical(sort(x),par_sort2(x))

p <- microbenchmark(sort(x),
                    par_sort(x),
                    par_sort2(x), times = 10)

p

# Rank
identical(rank(x),par_rank(x))
identical(data.table::frankv(x),par_rank(x))

p <- microbenchmark(rank(x),
                    data.table::frankv(x),
                    par_rank(x),
                    par_rank(x, threads = 4), times = 10)

p
