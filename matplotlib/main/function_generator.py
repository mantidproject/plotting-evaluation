import numpy as np


def function_generator(index, x_min, d_x, x_max):
    """

    Args:
        index:

    Returns:

    """
    # check
    assert x_min < x_max and d_x > 0

    # create X-array
    vec_x = np.arange(x_min, x_max, d_x)

    # calculate y
    index %= 4

    if index == 0:
        vec_y = np.sin(vec_x)

    elif index == 1:
        vec_y = np.exp(vec_x)

    elif index == 3:
        vec_y = 2*vec_x

    else:
        vec_y = np.exp(-(vec_x-5)**2*0.01)

    return vec_x, vec_y


if __name__ == '__main__':
    function_generator(0, 0, 0.5, 10.)
