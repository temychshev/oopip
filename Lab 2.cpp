#include <iostream> 
#include <cmath> 
#include <exception>  

class CustomException : public std::exception { // Наследуем от std::exception 
public:
    CustomException(const std::string& message, int code) : message_(message), code_(code) {}

    const char* what() const noexcept override { // Переопределяем метод what() 
        return message_.c_str();
    }

    int getCode() const {
        return code_;
    }

    // Коды ошибок 
    static const int ERROR_M_LESS_THAN_2 = 1;
    static const int ERROR_ZERO_DENOMINATOR = 2;
    static const int ERROR_M_LESS_THAN_MINUS_2 = 3;
    static const int ERROR_INVALID_M_VALUE = 4;

private:
    std::string message_;
    int code_;
};

double calculateZ1(double m) {
    // Проверяем, является ли m недопустимым значением (0 или -1) 
    if (m == 0 || m == -1) {
        throw CustomException("Ошибка: недопустимое значение m", CustomException::ERROR_INVALID_M_VALUE);
    }

    // Проверяем, соответствует ли m условию m > 2 
    if (m <= 2) {
        throw CustomException("Ошибка: m должно быть больше 2", CustomException::ERROR_M_LESS_THAN_2);
    }

    double numerator = sqrt(2 * m + 2 * sqrt(m * m - 4));
    double denominator = m + sqrt(m * m - 4 + 2);

    // Проверяем деление на ноль в знаменателе 
    if (denominator == 0) {
        throw CustomException("Ошибка: деление на ноль в знаменателе", CustomException::ERROR_ZERO_DENOMINATOR);
    }

    // Возвращаем результат 
    return numerator / denominator;
}

double calculateZ2(double m) {
    // Проверяем, является ли m недопустимым значением (0 или -1) 
    if (m == 0 || m == -1) {
        throw CustomException("Ошибка: недопустимое значение m", CustomException::ERROR_INVALID_M_VALUE);
    }

    // Проверяем, соответствует ли m условию m > -2 
    if (m <= -2) {
        throw CustomException("Ошибка: m должно быть больше -2", CustomException::ERROR_M_LESS_THAN_MINUS_2);
    }

    double denominator = sqrt(m + 2);

    // Проверяем деление на ноль в знаменателе 
    if (denominator == 0) {
        throw CustomException("Ошибка: деление на ноль в знаменателе", CustomException::ERROR_ZERO_DENOMINATOR);
    }

    return 1 / denominator;
}

int main() {
    setlocale(LC_ALL, "RU");
    double m;

    // Запрашиваем значение m от пользователя 
    std::cout << "Введите значение m: ";
    std::cin >> m;

    try {
        // Вычисляем Z1 и Z2 и сравниваем их 
        double z1 = calculateZ1(m);
        double z2 = calculateZ2(m);

        if (std::abs(z1 - z2) < 3) {
            std::cout << "Z1 и Z2 приблизительно одинаковы." << std::endl;
        }
        else {
            std::cout << "Z1 и Z2 различаются." << std::endl;
        }


        std::cout << z1 << '\n';
        std::cout << z2;
    }
    catch (const CustomException& e) {
        // Обрабатываем исключение и выводим сообщение об ошибке 
        std::cerr << "Исключение: " << e.what() << " (код: " << e.getCode() << ")" << std::endl;
    }

    return 0;
}