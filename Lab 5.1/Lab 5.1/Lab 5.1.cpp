#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

int main() {
    setlocale(LC_ALL, "Russian");

    std::ofstream inputFile("D:\\Programs\\Microsoft Visual Studio\\input.txt");
    std::ofstream outputFile("D:\\Programs\\Microsoft Visual Studio\\output.txt");

    if (inputFile.is_open() && outputFile.is_open()) {
        srand(static_cast<unsigned int>(time(0)));

        // Заполнение файла input.txt рандомными числами от -50 до 50
        for (int i = 0; i < 100; i++) {
            int number = rand() % 101 - 50; // Генерируем число от -50 до 50
            inputFile << number << std::endl;
        }
        inputFile.close();

        // Чтение чисел из input.txt, деление на 2, и запись в вектор
        std::vector<int> numbers;
        std::ifstream inputFileRead("D:\\Programs\\Microsoft Visual Studio\\input.txt");
        int number;
        while (inputFileRead >> number) {
            numbers.push_back(number / 2);
        }
        inputFileRead.close();

        // Сортировка вектора чисел
        std::sort(numbers.begin(), numbers.end());

        // Запись отсортированных чисел в output.txt
        for (int i = 0; i < numbers.size(); i++) {
            outputFile << numbers[i] << std::endl;
        }
        outputFile.close();

        std::cout << "Преобразование завершено. Результат записан в файл output.txt." << std::endl;
    }
    else {
        std::cout << "Не удалось открыть файлы." << std::endl;
    }

    return 0;
}
