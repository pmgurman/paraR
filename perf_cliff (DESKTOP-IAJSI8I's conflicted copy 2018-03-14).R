library(microbenchmark)
library(paraR)
library(dplyr)
library(ggplot2)

results <- data.frame()
for(i in c(1E2,1E3,1E4,1E5,1E6,1E7,1E8)) {
  x <- matrix(rnorm(i),nrow = sqrt(i))

  p <- microbenchmark::microbenchmark(sort(x),
                      sort(x,method = 'shell'),
                      sort(x,method = 'quick'),
                      sort(x,method = 'radix'),
                      par_sort(x)
                      ,times = 1000, unit = "ms")
  results <- rbind(results,cbind(x_length = prod(dim(x)), summary(p)[,c("expr","mean")]))
}



p <- results %>% ggplot(aes(x = x_length, y = mean, colour = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_path()

ggsave("test.png", p)

results <- data.frame()
for(i in round(10^seq(1, 3,by = 0.1))^2) {
  x <- matrix(rnorm(i),nrow = sqrt(i))

  p <-microbenchmark(colSums(x),
                     par_colSums(x, threads = 1),
                     par_colSums(x, threads = 2),
                     par_colSums2(x, threads = 1),
                     par_colSums2(x, threads = 2),
                     matrixStats::colSums2(x)
                                      ,times = 100, unit = "ms")
  results <- rbind(results,cbind(x_length = prod(dim(x)), summary(p)[,c("expr","mean")]))
}

p <- results %>% ggplot(aes(x = x_length, y = mean, colour = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_path()
p

ggsave("test.png", p)

results <- data.frame()
for(i in round(10^seq(1, 5,by = 0.25))) {
  x <- rnorm(i)
  p <-microbenchmark(mean(x),
                     par_mean(x),
                     par_sum(x),
                     par_sum(x, threads = 2),
                     par_sum2(x),
                     times = 1000, unit = "ms")
  results <- rbind(results,cbind(x_length = length(x), summary(p)[,c("expr","mean")]))
}

library(dplyr)
library(ggplot2)

results %>% ggplot(aes(x = x_length, y = mean, colour = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_smooth()
