
#include <iostream>
#include <ctime>
#include <stack>
#include <deque>
using namespace std;
struct point {
    int x;
    int y;
};
struct point_search : point {
    bool up;
    bool right;
    bool down;
    bool left;
};
class Task // задача
{
public:
    void virtual solve_task() = 0; // решить задачу
};

class labyrinth : public Task
{
    point in;
    point out;
    point_search p_search;
    stack <point_search> path;
    int count;
    bool** matrix;
public:
    labyrinth(bool** matrix_lab, int count);
    void solve_task()override;
    void set_in(int x, int y);
    void set_out(int x, int y);
    ~labyrinth();
};

labyrinth::labyrinth(bool** matrix_lab, int count) {
    bool* p_matrix_lab = (bool*)matrix_lab;
    this->count = count;
    matrix = new bool* [count];
    for (int i = 0; i < count; i++) {
        matrix[i] = new bool[count];
    }
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            matrix[i][j] = p_matrix_lab[i * count + j];
        }
    }
    cout << "\tЛабиринт :" << endl << endl;

    for (int i = 0; i < count; i++) {
        cout << "\t";
        for (int j = 0; j < count; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void labyrinth::solve_task(){
    if (in.x < 0 || in.x >= count || in.y < 0 || in.y >= count) cout << "Ошибка, точка входа выходит за границы лабиринта" << endl;
    else if (out.x < 0 || out.x >= count || out.y < 0 || out.y >= count) cout << "Ошибка, точка выхода выходит за границы лабиринта" << endl;
    else if (matrix[in.y][in.x]) cout << "Ошибка, в точке входа в лабиринт стена" << endl;
    else if (matrix[out.y][out.x]) cout << "Ошибка, в точке выхода из лабиринта стена" << endl;
    else {
        cout << "Начало программы, поиск выхода из лабиринта" << endl;
        cout << "Точка входа в лабиринт x, y: " << in.x << " " << in.y << endl;
        cout << "Точка выхода из лабиринта x, y: " << out.x << " " << out.y << endl;

        p_search.x = in.x;
        p_search.y = in.y;

        bool** path_matrix = new bool* [count];
        for (int i = 0; i < count; i++) {
            path_matrix[i] = new bool[count];
        }

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                path_matrix[i][j] = false;
            }
        }
        bool first_point = false;
        bool no_exit = false;
        while (p_search.x != out.x || p_search.y != out.y) {
            if (!path_matrix[p_search.y][p_search.x]) path_matrix[p_search.y][p_search.x] = true;
            p_search.up = false;
            p_search.right = false;
            p_search.down = false;
            p_search.left = false;
            if (p_search.y > 0) {
                if (!matrix[p_search.y - 1][p_search.x] && !path_matrix[p_search.y - 1][p_search.x]) {
                    p_search.up = true;
                }
            }
            if (p_search.x <= count - 2) {
                if (!matrix[p_search.y][p_search.x + 1] && !path_matrix[p_search.y][p_search.x + 1]) {
                    p_search.right = true;
                }
            }
            if (p_search.y <= count - 2) {
                if (!matrix[p_search.y + 1][p_search.x] && !path_matrix[p_search.y + 1][p_search.x]) {
                    p_search.down = true;
                }
            }
            if (p_search.x > 0) {
                if (!matrix[p_search.y][p_search.x - 1] && !path_matrix[p_search.y][p_search.x - 1]) {
                    p_search.left = true;
                }
            }
            if (!first_point) {
                path.push(p_search);
                first_point = true;
            }
            if (p_search.up) {// если можно пойти наверх
                p_search.y--;
                path.push(p_search);
                continue;
            }
            if (p_search.right) {// если можно пойти направо
                p_search.x++;
                path.push(p_search);
                continue;
            }
            if (p_search.down) {// если можно пойти вниз
                p_search.y++;
                path.push(p_search);
                continue;
            }
            if (p_search.left) {// если можно пойти налево
                p_search.x--;
                path.push(p_search);
                continue;
            }
            if (p_search.x == in.x && p_search.y == in.y && !p_search.up && !p_search.right && !p_search.down && !p_search.left) {
                cout << "Из лабиринта нет выхода!";
                no_exit = true;
                break;
            }
            path.pop();
            p_search = path.top();
        }

        if (!no_exit) { // если выход найден
            for (int i = 0; i < count; i++) {
                for (int j = 0; j < count; j++) {
                    path_matrix[i][j] = false;
                }
            }
            auto deq = path._Get_container();
            int i = 0;
            do {
                path_matrix[deq[i].y][deq[i].x] = true;
                i++;
            } while (deq[i].x != out.x || deq[i].y != out.y);
            path_matrix[deq[i].y][deq[i].x] = true;
            cout << "\tПуть лабиринта:" << endl;
            for (int i = 0; i < count; i++) {
                cout << "\t";
                for (int j = 0; j < count; j++) {
                    if (path_matrix[i][j]) cout << "* ";
                    else cout << "  ";
                }
                cout << endl;
            }
            i = 0;
            cout << endl << "\tКоординаты точек пути:" << endl;
            cout << "\t{x, y}" << endl;
            do {
                cout << "\t{" << deq[i].x << ", " << deq[i].y << "}" << endl;
                i++;
            } while (deq[i].x != out.x || deq[i].y != out.y);
            cout << "\t{" << deq[i].x << ", " << deq[i].y << "}" << endl;

        }

        for (int i = 0; i < count; i++) {
            delete[] path_matrix[i];
        }
        delete[] path_matrix;
    }

}
void labyrinth::set_in(int x, int y) {
    in.x = x;
    in.y = y;
}
void labyrinth::set_out(int x, int y) {
    out.x = x;
    out.y = y;
}
labyrinth::~labyrinth(){
    for (int i = 0; i < count; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
class user
{
public:
    void To_Do_Working(Task& job)
    {
        job.solve_task();
    }
};
int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    const int size_matrix = 20;
    bool matrix[20][20] = // вход 0 3, выход 17 19
    {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,1,0,1,1,1,0,1,1,1,0,0,0,0,1,1},
    {1,1,1,0,0,0,0,1,1,1,0,1,1,1,0,1,1,0,0,1},
    {0,0,0,0,1,0,1,1,0,0,0,1,0,1,0,1,1,0,1,1},
    {1,0,1,1,1,0,1,1,1,1,0,0,0,0,0,1,0,0,1,1},
    {1,0,1,1,1,0,1,0,0,0,1,0,1,1,1,1,1,0,1,1},
    {1,0,0,0,1,1,0,0,1,0,0,0,0,1,1,1,1,0,1,1},
    {1,1,1,0,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1,1},
    {1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,1,1,1,0,1,0,0,0,1,1,1,1,0,1,0,0,1},
    {1,0,0,0,0,1,0,1,1,1,0,0,0,1,0,0,0,0,1,1},
    {1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1},
    {1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1},
    {0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
    {0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,1,1},
    {0,1,0,0,1,1,1,0,1,1,1,1,0,1,1,1,0,0,1,1},
    {1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1},
    {1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,1,1,1,1,1},
    {1,0,1,1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1}
    };
    labyrinth lab((bool**)matrix, size_matrix);
    user user;
    cout << endl << "Введите координаты входа в лабиринт x, y:" << endl;
    int x, y;
    cin >> x >> y;
    lab.set_in(x, y);
    cout << endl << "Введите координаты выхода из лабиринта x, y:" << endl;
    cin >> x >> y;
    lab.set_out(x, y);
    user.To_Do_Working(lab);
    system("pause");
}

