import sys
import math
import numpy as np
from numpy.polynomial.chebyshev import Chebyshev

FUNCTIONS = {
    "exp2": {
        "func": lambda x: np.exp2(x),
        "domain": [0, 1],
        "degree": 9,
    },
    "sin": {
        "func": lambda x: np.sin(x * math.pi),
        "domain": [-1, 1],
        "degree": 13,
    },
    "sqrt": {
        "func": lambda x: np.sqrt(1 + x),
        "domain": [0, 1],
        "degree": 5,
    },
    "log2": {
        "func": lambda x: np.log2(1 + x),
        "domain": [0.5, 1],
        "degree": 9,
    },
}


def helper():
    print("")
    print(f"{sys.argv[0]} <function>")
    print("")
    print("Valid functions:")
    print("    - exp2")
    print("    - sin")
    print("    - sqrt")
    print("    - log2")


def coefficients(function: str):
    f = FUNCTIONS[function]
    x = np.linspace(f["domain"][0], f["domain"][1], 10000)
    y = f["func"](x)
    cheb_fit = Chebyshev.fit(x, y, f["degree"], domain=f["domain"])
    poly = cheb_fit.convert(kind=np.polynomial.Polynomial)
    print(poly.coef)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Invalid number of arguments")
        helper()
        sys.exit(-1)

    if FUNCTIONS.get(sys.argv[1]) is None:
        print("Invalid input function")
        helper()
        sys.exit(-1)

    coefficients(sys.argv[1])
    sys.exit(0)
