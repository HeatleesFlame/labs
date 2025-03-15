#include <iostream>
#include <cstdio>
#include <cstring>
#include <fcntl.h>

int main() {
    // Использование cin и cout
    std::cout << "Введите строку: ";
    char input[100];
    std::cin.getline(input, 100);

    // Использование scanf и printf
    int number;
    printf("Введите число: ");
    scanf("%d", &number);
    printf("Вы ввели число: %d\n", number);

    // Использование fopen и fclose
    FILE *file = fopen("example.txt", "w");
    if (file == nullptr) {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Использование fprintf для записи в файл
    fprintf(file, "Строка: %s\nЧисло: %d\n", input, number);
    fclose(file);

    // Использование fopen для чтения из файла
    file = fopen("example.txt", "r");
    if (file == nullptr) {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Использование fscanf для чтения из файла
    char fileInput[100];
    int fileNumber;
    fscanf(file, "Строка: %s\nЧисло: %d\n", fileInput, &fileNumber);
    printf("Прочитано из файла: Строка: %s, Число: %d\n", fileInput, fileNumber);
    fclose(file);

    // Использование open, read, write
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Ошибка открытия файла");
        return 1;
    }

    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("Ошибка чтения файла");
        close(fd);
        return 1;
    }

    buffer[bytesRead] = '\0';
    printf("Содержимое файла (read): %s\n", buffer);
    close(fd);

    // Использование feof
    file = fopen("example.txt", "r");
    if (file == nullptr) {
        perror("Ошибка открытия файла");
        return 1;
    }

    while (!feof(file)) {
        char ch = fgetc(file);
        if (ch == EOF) {
            if (feof(file)) {
                printf("\nДостигнут конец файла.\n");
            } else {
                perror("Ошибка чтения файла");
            }
            break;
        }
        putchar(ch);
    }

    fclose(file);

    return 0;
}