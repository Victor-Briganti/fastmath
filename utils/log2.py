import numpy as np
from numpy.polynomial.chebyshev import Chebyshev

f = lambda x: np.log2(1 + x)
x = np.linspace(0.5, 1, 10000)
y = f(x)
cheb_fit = Chebyshev.fit(x, y, 9, domain=[0.5, 1])
poly = cheb_fit.convert(kind=np.polynomial.Polynomial)
print(poly.coef)
