x <- file("task_1_capital.txt", open = "r")
valuesstr <- read.table(x)
axes <- valuesstr[1,]
values <- matrix(1, length(valuesstr[,1]), length(valuesstr[1,]))
for (i in 2:length(valuesstr[,1])){
  values[i,1] <- as.integer(as.character(valuesstr[i,1]))
  values[i,2] <- as.integer(as.character(valuesstr[i,2]))
}

w = values[-1,1]
y = values[-1,2]
inversed = ginv(w)
x = inversed * y
plot(values[-1,1], x * w)
