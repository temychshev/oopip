#include <iostream>
#include <iomanip>


// Манипулятор для вывода всех символов большими и чисел в OCT формате
std::ostream& uppercase_oct(std::ostream& os) {
    return os << std::uppercase << std::oct;
}

// Манипулятор для вывода всех символов маленькими и замены пробелов на #
std::ostream& lowercase_replace_space(std::ostream& os) {
    return os << std::nouppercase << std::hex << std::setfill('#') << std::setw(2);
}

// Манипулятор для вывода всех чисел в HEX формате и без пробелов
std::ostream& hex_no_space(std::ostream& os) {
    return os << std::hex << std::setfill('0') << std::setw(2);
}

int main() {

    setlocale(LC_ALL, "Russian");


    char ch = 'A';
    int num = 456;
    std::string str = "Aaaa";

    // Пример использования манипуляторов
    std::cout << "1) Вывод всех символов большими и чисел в OCT формате: ";
    std::cout << uppercase_oct << ch << " " << num << " " << str << std::endl;

    std::cout << "2) Вывод всех символов маленькими, замена пробелов на #: ";
    std::cout << lowercase_replace_space << ch << '#' << num << '#' << str << std::endl;

    std::cout << "3) Вывод всех чисел в HEX формате без пробелов: ";
    std::cout << hex_no_space << ch << " " << num << " " << str << std::endl;

    return 0;
}