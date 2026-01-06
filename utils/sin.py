import numpy as np
import math
from numpy.polynomial.chebyshev import Chebyshev

f = lambda x: np.sin(x * math.pi)
x = np.linspace(-1, 1, 10000)
y = f(x)
cheb_fit = Chebyshev.fit(x, y, 13, domain=[0, 1])
poly = cheb_fit.convert(kind=np.polynomial.Polynomial)
print(poly.coef)
