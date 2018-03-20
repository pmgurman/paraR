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
for(i in c(10^c(1,2,3,4),10^c(2,3,4)/2)) {
  x <- matrix(rnorm(i^2),nrow = i)

  p <-microbenchmark(colSums(x),
                     par_colSums(x, threads = 2),
                     paraR:::par_colSums2(x, threads = 2),
                     matrixStats::colSums2(x)
                                      ,times = 10, unit = "ms")
  results <- rbind(results,cbind(x_length = prod(dim(x)), summary(p)[,c("expr","mean")]))
}

p <- results %>% ggplot(aes(x = x_length, y = mean, colour = expr, group = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_line()
p

ggsave("test.png", p)

results <- data.frame()
for(i in 10^c(2,3,4,5,6,7,8)) {
  print(i)
  x <- rnorm(i)
  p <-microbenchmark(par_mean(x), mean(x), par_sum(x), par_sum2(x)
                     ,times = 10, unit = "ms")
  results <- rbind(results,cbind(x_length = length(x), summary(p)[,c("expr","median")]))
}

library(dplyr)
library(ggplot2)

results %>% ggplot(aes(x = x_length, y = median, colour = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_path()





# Dist matrix

results <- data.frame()
for(i in sort(c(10^c(1,2,3,4),10^c(2,3,4)/2))) {
  print(i)
  x <- matrix(rnorm(i^2),nrow = i)

  p <-microbenchmark(
                     par_dist(x)
                     ,times = 10, unit = "ms")
  results <- rbind(results,cbind(x_length = prod(dim(x)), summary(p)[,c("expr","median")]))
}

p <- results %>% ggplot(aes(x = x_length, y = median, colour = expr, group = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_line()
ggsave("test.png",p)
