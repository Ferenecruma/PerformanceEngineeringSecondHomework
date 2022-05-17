import random

from timebudget import timebudget
import numpy as np

ARRAY_SIZE = 10000000
DOUBLE_ARRAY_1 = [random.random() for _ in range(ARRAY_SIZE)]
DOUBLE_ARRAY_2 = [random.random() for _ in range(ARRAY_SIZE)]

@timebudget
def elemwise_python(list_1: list[float], list_2: list[float]):
    return [e1 * e2 for e1, e2 in zip(list_1, list_2)]

@timebudget
def elemwise_numpy(array_1: np.ndarray, array_2: np.ndarray):
    return array_1 * array_2


def main():
    elemwise_numpy(np.array(DOUBLE_ARRAY_1), np.array(DOUBLE_ARRAY_2))
    elemwise_python(DOUBLE_ARRAY_1, DOUBLE_ARRAY_2)

if __name__ == "__main__":
    main()