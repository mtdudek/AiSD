
from random import randint

# down -> increase x
# right -> increase y
def step_down_left(x, y, m, n):
    if x + 2 >= m or y - 1 < 0:
        return None
    return (x + 2, y - 1)

def step_down_right(x, y, m, n):
    if x + 2 >= m or y + 1 >= n:
        return None
    return (x + 2, y + 1)

def step_up_left(x, y, m, n):
    if x - 1 < 0 or y - 2 < 0:
        return None
    return (x - 1, y - 2)

def step_up_right(x, y, m, n):
    if x - 1 < 0 or y + 2 >= n:
        return None
    return (x - 1, y + 2)

def find_max(A, x, y, m, n, went_up = False, rec_level = 0):
    if x == m - 1:
        yield ([(x, y)], A[x][y])
    else:
        for (f, goes_up) in [(step_down_left, False), (step_down_right, False)] + \
                [(step_up_left, True), (step_up_right, True)] * (not went_up):
            newXY = f(x, y, m, n)
            if newXY:
                for (path, value) in find_max(A, newXY[0], newXY[1], m, n, goes_up, rec_level + 1):
                    yield ([(x, y)] + path , A[x][y] + value)

def helllo(n=0):
    if n == 5:
        yield ([n],n)
    else:
        for i in range(2):
            for (path, num) in helllo(n + 1):
                yield ([n + i] + path, n + i + num)


for _ in range(0, 100):
    # zmienna _ będzie numerem wygenerowanego testu, który będzie w nazwach plików z tetami, czyli test{_}.in, test{_}.out
    m = randint(3,10) # liczba wierszy
    n = randint(3,20)  # liczba kolumn

    test_data = [[randint(0, 9) for _ in range(n)] for _ in range(m)]
    f = open(f"test{_}.in","w+")
    f.write(f"{m} {n}\n")
    for row in test_data:
        f.write("".join(map(str, row)) + "\n")
    f.close()

    powers_of_test_data = [[7 ** elem for elem in row] for row in test_data]
    max = 0
    for y in range(n):
        for (path, value) in find_max(powers_of_test_data, 0, y, m, n):

            if max < value:
                max = value

    f = open(f"test{_}.out","w+")
    f.write(str(max))
    f.close()
