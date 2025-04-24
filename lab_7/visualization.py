import matplotlib.pyplot as plt
import numpy as np

def plot_lines(coeff_matrix):
    """
    Строит графики прямых, заданных матрицей коэффициентов в форме Ax + By + C = 0.

    Параметры:
    coeff_matrix (list of list): Матрица коэффициентов, где каждая строка [A, B, C] 
                                 соответствует уравнению прямой.
    """
    plt.figure(figsize=(8, 6))
    x = np.linspace(-10, 10, 400)  # Диапазон значений x

    for i, (A, B, C) in enumerate(coeff_matrix):
        # Пропускаем некорректные уравнения (A и B оба нули)
        if A == 0 and B == 0:
            print(f"Пропуск строки {i}: недопустимые коэффициенты A=0 и B=0.")
            continue

        label = f"{A}x + {B}y + {C} = 0"

        # Вертикальная прямая (B = 0)
        if B == 0:
            x_val = -C / A if A != 0 else 0
            plt.axvline(x=x_val, label=label, linestyle='--')
        
        # Горизонтальная или наклонная прямая
        else:
            y = (-A/B) * x + (-C/B)
            plt.plot(x, y, label=label)

    plt.title('Графики прямых')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.grid(True)
    plt.xlim(-10, 10)
    plt.ylim(-10, 10)
    plt.show()

if __name__ == "__main__":
    m, n = list(
        map(int, input().split(' '))
    )
    coeff_matrix = []
    for i in range(m):
        coeff_matrix.append(
            list(map(int, input().split(" "))
            ))
    plot_lines(coeff_matrix=coeff_matrix)
