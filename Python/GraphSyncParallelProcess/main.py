import threading

# Определение порогового графа
graph = {
    1: [],
    2: [1],
    3: [1],
    4: [2, 3],
    5: [4]
}

# Массив для суммирования
array = [1, 2, 3, 4, 5]

# Создание словаря блокировок для каждой вершины графа
lock_dict = {node: threading.Event() for node in graph}

# Функция для суммирования элементов массива
def sum_elements(start_index, end_index):
    result = sum(array[start_index:end_index+1])
    print(f"Sum of elements from index {start_index} to {end_index}: {result}")
    lock_dict[start_index].set()

# Создание и запуск потоков для каждой вершины графа
threads = []
for node in graph:
    predecessors = graph[node]
    if len(predecessors) == 0:
        start_index = 0
    else:
        start_index = max(predecessors)
    end_index = node - 1
    t = threading.Thread(target=sum_elements, args=(start_index, end_index))
    threads.append(t)
    t.start()

# Ожидание завершения всех потоков
for t in threads:
    t.join()

print("All processes have finished.")
