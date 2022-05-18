from functools import wraps
import time
import random

import numpy as np


ARRAY_SIZES = [1000, 10_000, 100_000, 1_000_000, 10_000_000, 100_000_000]


def timeit(func):
    @wraps(func)
    def timeit_wrapper(*args, **kwargs):
        start_time = time.perf_counter_ns()
        result = func(*args, **kwargs)
        end_time = time.perf_counter_ns()
        total_time = end_time - start_time
        print(f'Function {func.__name__} Took {total_time} nanoseconds \n')
        with open("nanoseconds.txt", "a") as f:
            f.write(f'{total_time} \n')
        return result
    return timeit_wrapper


def create_random_lists(list_size: int) -> tuple[list, list]:
    return [random.random() for _ in range(list_size)], [random.random() for _ in range(list_size)]

@timeit
def elemwise_python(list_1: list[float], list_2: list[float]):
    return [e1 * e2 for e1, e2 in zip(list_1, list_2)]

@timeit
def elemwise_numpy(array_1: np.ndarray, array_2: np.ndarray):
    return array_1 * array_2


def main():
    for size in ARRAY_SIZES:
        print(f'\n\nArray size: {size} \n')
        list_1, list_2 = create_random_lists(size)
        elemwise_python(list_1, list_2)
        elemwise_numpy(np.array(list_1), np.array(list_2))

if __name__ == "__main__":
    main()