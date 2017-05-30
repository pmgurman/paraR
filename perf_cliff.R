library(microbenchmark)

results <- data.frame()
for(i in c(1E2,1E3,1E4,1E5,1E6,1E7,1E8,5E7)) {
  x <- matrix(rnorm(i),nrow = sqrt(i))

  p <- microbenchmark::microbenchmark(sort(x),
                      sort(x,method = 'shell'),
                      sort(x,method = 'quick'),
                      sort(x,method = 'radix')
                      ,times = 100, unit = "ms")
  results <- rbind(results,cbind(x_length = prod(dim(x)), summary(p)[,c("expr","mean")]))
}

library(dplyr)
library(ggplot2)

results %>% ggplot(aes(x = x_length, y = mean, colour = expr)) +
  geom_point() +
  scale_x_log10() +
  scale_y_log10() +
  geom_path()
