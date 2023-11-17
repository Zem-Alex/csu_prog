import numpy as np
import matplotlib.pyplot as plt

# Данные из таблицы
f_exp = np.array([4, 8, 12,	16,	20,	40,	60,	80,	100]) # в кГц
Um_out_exp = np.array([0.98, 1.85, 2.57, 3.17, 3.535, 4.41,	4.66, 4.78,	4.88]) # в В

# Заданные значения
R1 = 100 # 100 Ом
C1 = 80e-9 # 100 нФ
f = np.linspace(1, 1000, 1000) # Генерация 1000 частот от 1 Гц до 1000 Гц
w = 2 * np.pi * f # Угловая частота в рад/с

# Расчет аналитических характеристик
K = w * R1 * C1 / np.sqrt(1 + (w * R1 * C1)**2)
phi = np.arctan(w * R1 * C1)

# Построение графика
plt.figure(figsize=(10, 6))
plt.semilogx(f, 20 * np.log10(K), label='Расчетная АЧХ (дБ)')
plt.xlabel('Частота (Гц)')
plt.ylabel('Амплитуда (дБ)')
plt.title('АЧХ и ФЧХ')
plt.twinx()
plt.semilogx(f, np.degrees(phi), 'r', label='Расчетная ФЧХ (градусы)')
plt.ylabel('Фаза (градусы)')

# Добавляем экспериментальные данные
plt.plot(f_exp, 20 * np.log10(Um_out_exp), 'bo', label='Экспериментальная АЧХ (дБ)')

# Отображаем легенду
plt.legend(loc='upper left')

# Отображаем график
plt.show()