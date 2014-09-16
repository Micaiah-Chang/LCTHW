from nose.tools import assert_equal
from stats import Stats
import math

samples = [ 6.1061334, 9.6783204, 1.2747090, 8.2395131, 0.3333483,
    6.9755066, 1.0626275, 7.6587523, 4.9382973, 9.5788115]

expect = Stats(s_sumsq=425.1641, s_sum=55.84602,  s_min=0.333,  s_max=9.678, s_n=10)

def assert_float_equal(X,Y):
    N = 3 # Power with which to raise
    assert_equal((round(X * math.pow(10, N))), (round(Y * math.pow(10,N))))

def operations_test():
    st = Stats()

    for sample in samples:
        st.sample(sample)

    print st

    assert_float_equal(expect.sum, st.sum)
    assert_float_equal(expect.sumsq, st.sumsq)
    assert_equal(expect.n, st.n)
    assert_float_equal(expect.min, st.min)
    assert_float_equal(expect.max, st.max)

if __name__ == '__main__':
    operations_test()
