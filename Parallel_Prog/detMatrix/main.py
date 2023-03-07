import random
import threading

class Matrix:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.data = [[0 for j in range(cols)] for i in range(rows)]

    def randomize(self):
        for i in range(self.rows):
            for j in range(self.cols):
                self.data[i][j] = random.randint(0, 9)

    def multiply(self, other):
        if self.cols != other.rows:
            raise ValueError("Number of columns in first matrix must match number of rows in second matrix.")
        result = Matrix(self.rows, other.cols)
        threads = []
        for i in range(self.rows):
            for j in range(other.cols):
                thread = threading.Thread(target=self._multiply_element, args=(i, j, other, result))
                thread.start()
                threads.append(thread)
        for thread in threads:
            thread.join()
        return result

    def _multiply_element(self, i, j, other, result):
        sum = 0
        for k in range(self.cols):
            sum += self.data[i][k] * other.data[k][j]
        result.data[i][j] = sum

    def print(self):
        for i in range(self.rows):
            print(self.data[i])

N = int(input("Enter matrix size: "))
M = int(input("Enter matrix size: "))

matrix1 = Matrix(N, M)
matrix1.randomize()

N2 = int(input("Enter matrix size: "))
M2 = int(input("Enter matrix size: "))
matrix2 = Matrix(N2, M2)
matrix2.randomize()

result = matrix1.multiply(matrix2)

print("Matrix 1:")
matrix1.print()

print("Matrix 2:")
matrix2.print()

print("Result:")
result.print()
