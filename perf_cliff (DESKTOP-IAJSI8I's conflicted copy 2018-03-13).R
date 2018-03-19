library(microbenchmark)
library(paraR)
library(dplyr)
library(ggplot2)

results <- data.frame()
for(i in c(1E2,1E3,1E4,1E5)) {
  x <- matrix(rnorm(i),nrow = sqrt(i))

  p <- microbenchmark::microbenchmark(sort(x),
                      sort(x,method = 'shell'),
                      sort(x,method = 'quick'),
                      sort(x,method = 'radix'),
                      par_sort(x)
                      ,times = 1000, unit = "ms")
  results <- rbind(results,cbind(x_length = prod(dim(x)), summary(p)[,c("expr","mean")]))
}



results %>% ggplot(aes(x = x_length, y = mean, colour = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_path()



results <- data.frame()
for(i in round(10^seq(1, 7,by = 0.25))) {
  x <- matrix(rnorm(i),nrow = sqrt(i))

  colMeans(x) - par_colMeans(x)
  p <-microbenchmark(par_colMeans(x),
                     OMPutils:::par_colMeans(x, threads = 2),
                     OMPutils:::par_colMeans(x, threads = 4),
                     OMPutils:::par_colMeans2(x),
                     mean(x)
                                      ,times = 100, unit = "ms")
  results <- rbind(results,cbind(x_length = prod(dim(x)), summary(p)[,c("expr","mean")]))
}

results %>% ggplot(aes(x = x_length, y = mean, colour = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_path()


results <- data.frame()
for(i in round(10^seq(1, 8,by = 0.25))) {
  x <- rnorm(i)
  p <-microbenchmark(par_mean(x), mean(x)
                     ,times = 100, unit = "ms")
  results <- rbind(results,cbind(x_length = length(x), summary(p)[,c("expr","mean")]))
}

library(dplyr)
library(ggplot2)

results %>% ggplot(aes(x = x_length, y = mean, colour = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_path()
