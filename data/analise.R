setwd('~/Documents/mestrado/sist_recomendacao/tp1/data')
getwd()
data <- read.csv(file = 'ratings.csv', header = TRUE, sep = ',')
colnames(data)

num.items <- 10000
sampling <- sample(length(data$Prediction))[1:num.items]
samples <- data$Prediction[sampling]
barplot(table(samples))
p1 <- hist(samples, right=FALSE)

qqnorm(samples)

library(zoo)
breaks_cdf <- pgamma(p1$breaks, shape=10, scale=3)
null.probs <- rollapply(breaks_cdf, 2, function(x) x[2]-x[1])

barplot(breaks_cdf)

# goodness of fit test form gamma dist
a <- chisq.test(p1$counts, 
                p=null.probs,
                rescale.p = TRUE,
                simulate.p.value = TRUE)

hist(rnorm(100, 10, 2))

x.wei<-rweibull(n=200,shape=2.1,scale=1.1) 
x.teo<-rweibull(n=200,shape=2, scale=1) 

qqplot(x.teo,x.wei,main="QQ-plot distr. Weibull")
abline(0,1)
data$Prediction

ks.test(x.wei, 'pweibull', shape=2, scale=1)

install.packages('vcd')
library(vcd)
gf <- goodfit(data$Prediction, type="normal", method="MinChisq")
summary(gf)


hist(1 - rgamma(400, shape=20, scale=3))
barplot(table(samples))

library(MASS)
fit.w <- fitdistr(samples, "weibull")
shape <- fit.w$estimate[1]
scale <- fit.w$estimate[2]
qqplot(samples, rweibull(1000, shape, scale))

fit.p <- fitdistr(samples, "poisson")
shape <- fit.p$estimate[1]
qqplot(samples, rpois(1000, shape))

barplot(table(rpois(1000, shape)))

fit.g <- fitdistr(samples, "gamma")
shape <- fit.g$estimate[1]
scale <- fit.g$estimate[2]
qqplot(samples, rgamma(1000, shape, scale))

fit.p <- fitdistr(samples, "poisson")
qqplot(samples, rpois(1000, fit.p$estimate[1]))

hist(rgamma(1000, shape, scale))

install.packages('fitdistrplus')
library(fitdistrplus)

#Fit x data with fitdist
fit.w <- fitdist(samples, "weibull")
summary(fit.w)
plot(fit.w)

fit.g <- fitdist(samples, "gamma")
summary(fit.g)
plot(fit.g)

fit.l <- fitdist(samples, "lnorm")
summary(fit.l)
plot(fit.l)
?fitdist

samples.lnorm <- rlnorm(1000, 1.9320988, 0.3720317)
samples.weibull <- rweibull(1000, 4.591694, 7.940204)
hist(samples.weibull)
hist(samples.lnorm)

qqplot(samples, rweibull(1000, 4.591694, 7.940204))

install.packages('fBasics')
