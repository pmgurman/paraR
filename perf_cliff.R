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
                      ,times = 100, unit = "ms")
  results <- rbind(results,cbind(x_length = prod(dim(x)), summary(p)[,c("expr","mean")]))
}



p <- results %>% ggplot(aes(x = x_length, y = mean, colour = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_path()

ggsave("test.png", p)

results <- data.frame()
for(i in unique(round(10^seq(2, 3.5, by = 0.2)))) {
  print(i)
  x <- matrix(rnorm(i^2),nrow = i)

  p <-microbenchmark(colSums(x),
                     par_colSums(x),
                     matrixStats::colSums2(x)
                                      ,times = 100, unit = "ms")
  results <- rbind(results,cbind(x_length = prod(dim(x)), summary(p)[,c("expr","mean")]))
}

p <- results %>% ggplot(aes(x = x_length, y = mean, colour = expr, group = expr)) +
  scale_x_log10() +
  scale_y_log10() +
  geom_line()
p

ggsave("test.png", p)

results <- data.frame()
for(i in unique(round(10^seq(1, 8, by = 0.2)))) {
  print(i)
  x <- rnorm(i)
  # par_mean(x), mean(x),
  p <-microbenchmark(mean(x), par_mean(x), par_sum(x)
                      ,times = 10, unit = "ms")
  results <- rbind(results,cbind(x_length = length(x), summary(p)[,c("expr","median")]))
}



results %>% arrange(x_length) %>% ggplot(aes(x = x_length, y = median, colour = expr)) +
  scale_x_log10() +
  scale_y_log10() +
  geom_path()


results <- data.frame()
for(i in 10^c(2,3,4,5,6,7)) {
  print(i)
  x <- rnorm(i)
  # par_mean(x), mean(x),
  p <-microbenchmark( par_sum(x), par_sum2(x), par_sum3(x), par_sum4(x)
                     ,times = 10, unit = "ms")
  results <- rbind(results,cbind(x_length = length(x), summary(p)[,c("expr","median")]))
}



results %>% ggplot(aes(x = x_length, y = median, colour = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_path()





# Dist matrix

results <- data.frame()
for(i in sort(c(10^c(1,2,3),10^c(2,3)/4,10^c(2,3)/2))) {
  print(i)
  x <- matrix(rnorm(i^2),nrow = i)

  p <-microbenchmark(dist(x),
                     par_dist(x)
                     ,times = 10, unit = "ms")
  results <- rbind(results,cbind(x_length = prod(dim(x)), summary(p)[,c("expr","median")]))
}

p <- results %>% ggplot(aes(x = x_length, y = median, colour = expr, group = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_line()
ggsave("test2.png",p)
