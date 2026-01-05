import numpy as np
from numpy.polynomial.chebyshev import Chebyshev

f = lambda x: np.exp2(x)
x = np.linspace(0, 1, 10000)
y = f(x)
cheb_fit = Chebyshev.fit(x, y, 9, domain=[0, 1])
poly = cheb_fit.convert(kind=np.polynomial.Polynomial)
print(poly.coef)
