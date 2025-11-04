#include <iostream>
#include <memory>
#include <cmath>

#include "point.h"
#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"
#include "array.h"

int main() {
    using T = double;
    Array<std::shared_ptr<Figure<T>>> arr;

    std::cout << "Доступные команды:\n"
              << "  1 - добавить треугольник\n"
              << "  2 - добавить квадрат\n"
              << "  3 - добавить прямоугольник\n"
              << "  p - вывести все фигуры\n"
              << "  s - вычислить общую площадь\n"
              << "  d - удалить фигуру по индексу\n"
              << "  q - выход\n";

    while (true) {
        std::cout << ">>> ";
        char cmd;
        if (!(std::cin >> cmd)) break;
        if (cmd == 'q') break;

        if (cmd == '1') {
            std::cout << "Введите координаты: x1 y1 x2 y2 x3 y3\n";
            Triangle<T> t;
            std::cin >> t;
            arr.push_back(std::make_shared<Triangle<T>>(t));
            std::cout << "Треугольник добавлен.\n";
        }
        else if (cmd == '2') {
            std::cout << "Введите: центр_x центр_y сторона [угол_в_градусах]\n";
            Square<T> s;
            std::cin >> s;
            arr.push_back(std::make_shared<Square<T>>(s));
            std::cout << "Квадрат добавлен.\n";
        }
        else if (cmd == '3') {
            std::cout << "Введите: центр_x центр_y ширина высота [угол_в_градусах]\n";
            Rectangle<T> r;
            std::cin >> r;
            arr.push_back(std::make_shared<Rectangle<T>>(r));
            std::cout << "Прямоугольник добавлен.\n";
        }
        else if (cmd == 'p') {
            if (arr.size() == 0) {
                std::cout << "Массив пуст.\n";
            } else {
                for (size_t i = 0; i < arr.size(); ++i) {
                    std::cout << i << ": " << *arr[i] << "\n";
                }
            }
        }
        else if (cmd == 's') {
            double total = 0.0;
            for (size_t i = 0; i < arr.size(); ++i)
                total += arr[i]->area();
            std::cout << "Общая площадь: " << total << "\n";
        }
        else if (cmd == 'd') {
            std::cout << "Введите индекс для удаления: ";
            size_t idx;
            std::cin >> idx;
            try {
                arr.remove_at(idx);
                std::cout << "Фигура удалена.\n";
            } catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
        }
        else {
            std::cout << "Неизвестная команда.\n";
        }
    }

    std::cout << "Выход из программы.\n";
    return 0;
}
