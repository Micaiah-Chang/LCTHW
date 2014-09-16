import math

class Stats(object):

    def __init__(self, s_sum=0, s_sumsq=0, s_n=0, s_min=0, s_max=0):
        self.sum=s_sum
        self.sumsq=s_sumsq
        self.n = s_n
        self.min = s_min
        self.max = s_max

    def mean(self):
        return float(self.sum) / float(self.n)

    def stddeve(self):
        return math.sqrt(self.sumsq - (self.sum * self.sum / self.n) / (self.n - 1))

    def sample(self, s):
        self.sum += s
        self.sumsq += s*s

        if self.n == 0:
            self.min = s
            self.max = s
        else:
            if self.min > s:
                self.min = s
            if self.max < s:
                self.max = s

        self.n +=1

    def __str__(self):
        return str("sum: "+ str(self.sum)+"\n"+
                    "sumsq: "+ str(self.sumsq)+"\n"+
                    "n: "+ str(self.n)+"\n"+
                    "min: "+ str(self.min)+"\n"+
                    "max: "+str(self.max))
