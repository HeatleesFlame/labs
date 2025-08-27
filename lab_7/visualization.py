import matplotlib.pyplot as plt
import numpy as np

def plot_lines(coeff_matrix):

    plt.figure(figsize=(8, 6))
    x = np.linspace(-10, 10, 400)

    for i, (A, B, C) in enumerate(coeff_matrix):
        if A == 0 and B == 0:
            print(f"Пропуск строки {i}: недопустимые коэффициенты A=0 и B=0.")
            continue

        label = f"{A}x + {B}y + {C} = 0"

        if B == 0:
            x_val = -C / A if A != 0 else 0
            plt.axvline(x=x_val, label=label, linestyle='--')
        

        else:
            y = (-A/B) * x + (C/B)
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
    with open(r"C:\Users\D\Documents\tsu\C++\labs\lab_7\buff.txt", 'r') as f:
        # l = f.readline()
        # m, n = list(map(int, l.split(' ')[:-1]))
        coeff_matrix = []
        for line in f:
            coeff_matrix.append(list(map(int, line[:-2].split(" "))))
    plot_lines(coeff_matrix=coeff_matrix)

