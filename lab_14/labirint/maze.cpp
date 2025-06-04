#include <iostream>
#include <cstring>
#include <cstdlib>

const int MAX_SIZE = 22;
const int WALL = 1000;

struct Point {
    int row;
    int col;
};

void initialize_maze(int maze[MAX_SIZE][MAX_SIZE], int& n, Point& start, Point& end) {
    char line[MAX_SIZE];
    bool found_start = false;
    bool found_end = false;

    std::cout << "Введите размер лабиринта (n): ";
    std::cin >> n;
    std::cin.ignore();

    // Инициализация массива стенами
    std::memset(maze, WALL, sizeof(int) * MAX_SIZE * MAX_SIZE);

    std::cout << "Введите лабиринт (" << n << " строк):\n";
    for (int i = 1; i <= n; i++) {
        std::cin.getline(line, MAX_SIZE);
        
        for (int j = 1; j <= n; j++) {
            char c = line[j-1];
            
            if (c == 's' || c == 'S') {
                if (found_start) {
                    std::cerr << "Ошибка: Начальная точка задана более одного раза!\n";
                    exit(1);
                }
                start.row = i;
                start.col = j;
                found_start = true;
                maze[i][j] = 0;
            }
            else if (c == 'f' || c == 'F') {
                if (found_end) {
                    std::cerr << "Ошибка: Конечная точка задана более одного раза!\n";
                    exit(1);
                }
                end.row = i;
                end.col = j;
                found_end = true;
                maze[i][j] = 0;
            }
            else if (c == '.' || c == '-') {
                maze[i][j] = 0;
            }
            else if (c == '#') {
                maze[i][j] = WALL;
            }
            else {
                std::cerr << "Недопустимый символ: " << c << "\n";
                exit(1);
            }
        }
    }

    if (!found_start || !found_end) {
        std::cerr << "Ошибка: В лабиринте должна быть ровно одна начальная (s) и одна конечная (f) точки!\n";
        exit(1);
    }

    for (int j = 0; j <= n + 1; j++) {
        maze[0][j] = WALL;
        maze[n + 1][j] = WALL;
    }
    for (int i = 1; i <= n; i++) {
        maze[i][0] = WALL;
        maze[i][n + 1] = WALL;
    }
}

void bfs_marking(int maze[MAX_SIZE][MAX_SIZE], int n, Point start) {
    Point queue[MAX_SIZE * MAX_SIZE];
    int front = 0, rear = 0;

    if (maze[start.row][start.col] != 0) return;

    queue[rear++] = start;
    maze[start.row][start.col] = 1;

    const int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

    while (front < rear) {
        Point current = queue[front++];
        int next_value = maze[current.row][current.col] + 1;

        for (int i = 0; i < 8; i++) {
            Point next = {
                current.row + dx[i],
                current.col + dy[i]
            };

            if (maze[next.row][next.col] == 0) {
                maze[next.row][next.col] = next_value;
                queue[rear++] = next;
            }
        }
    }
}

void reconstruct_path(int maze[MAX_SIZE][MAX_SIZE], Point start, Point end, 
                     Point path[], int& path_length) {
    path_length = maze[end.row][end.col] - 1;
    Point current = end;

    const int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

    for (int step = path_length; step >= 0; step--) {
        path[step] = current;

        for (int i = 0; i < 8; i++) {
            Point prev = {
                current.row + dx[i],
                current.col + dy[i]
            };

            if (maze[prev.row][prev.col] == step) {
                current = prev;
                break;
            }
        }
    }
}

void print_maze_with_path(int maze[MAX_SIZE][MAX_SIZE], int n, 
                         Point path[], int path_length, Point start, Point end) {
    char display[MAX_SIZE][MAX_SIZE];

 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            display[i][j] = maze[i][j] == WALL ? '#' : '-';
        }
    }

  
    if (path_length > 0) {
        for (int k = 0; k <= path_length; k++) {
            Point p = path[k];
            display[p.row][p.col] = '*';
        }
      
        display[start.row][start.col] = 'S';
        display[end.row][end.col] = 'F';
    }

  
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cout << display[i][j];
        }
        std::cout << "\n";
    }
}

int main() {
    int n;
    Point start, end;
    int maze[MAX_SIZE][MAX_SIZE];
    
    initialize_maze(maze, n, start, end);
    bfs_marking(maze, n, start);
    
    if (maze[end.row][end.col] == 0 || maze[end.row][end.col] == WALL) {
        std::cout << "\nПуть не найден!\n";
        print_maze_with_path(maze, n, nullptr, 0, start, end);
        return 0;
    }
    
    Point path[MAX_SIZE * MAX_SIZE];
    int path_length;
    reconstruct_path(maze, start, end, path, path_length);
    
    std::cout << "\nКратчайший путь за " << path_length << " шагов:\n";
    print_maze_with_path(maze, n, path, path_length, start, end);
    
    return 0;
}