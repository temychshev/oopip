#include <iostream>

template<typename T>
class ShPtrArr {
private:
    T* data;
    int* refCount;
    size_t size;

public:
    // Конструктор по умолчанию
    ShPtrArr() : data(nullptr), refCount(nullptr), size(0) {}

    // Конструктор с параметрами
    explicit ShPtrArr(size_t size) : data(new T[size]), refCount(new int(1)), size(size) {}

    // Конструктор копирования
    ShPtrArr(const ShPtrArr& other) : data(other.data), refCount(other.refCount), size(other.size) {
        (*refCount)++;
    }

    // Деструктор
    ~ShPtrArr() {
        release();
    }

    // Оператор присваивания
    ShPtrArr& operator=(const ShPtrArr& other) {
        if (this != &other) {
            release();
            data = other.data;
            refCount = other.refCount;
            size = other.size;
            (*refCount)++;
        }
        return *this;
    }

    // Оператор индексирования
    T& operator[](size_t index) const {
        return data[index];
    }

    // Метод для получения указателя на данные
    T* get() const {
        return data;
    }

    // Метод для проверки на пустоту
    bool isEmpty() const {
        return (data == nullptr);
    }

private:
    // Метод для освобождения ресурсов
    void release() {
        if (refCount != nullptr) {
            (*refCount)--;
            if (*refCount == 0)
            {
                delete[] data;
                    delete refCount;
            }
        }
    }
};

int main() {
    // Пример использования шаблонного класса ShPtrArr
    ShPtrArr<int> arr1(5); // Создание smart-указателя на массив из 5 элементов типа int

    for (size_t i = 0; i < 5; i++) {
        arr1[i] = i + 1; // Инициализация элементов массива
    }

    ShPtrArr<int> arr2(arr1); // Копирование smart-указателя arr1 в arr2

    std::cout << "arr1: ";
    for (size_t i = 0; i < 5; i++) {
        std::cout << arr1[i] << " "; // Вывод элементов массива arr1
    }
    std::cout << std::endl;

    std::cout << "arr2: ";
    for (size_t i = 0; i < 5; i++) {
        std::cout << arr2[i] << " "; // Вывод элементов массива arr2
    }
    std::cout << std::endl;

    arr1[0] = 10; // Изменение значения элемента массива в arr1

    std::cout << "arr1[0]: " << arr1[0] << std::endl; // Вывод значения измененного элемента в arr1
    std::cout << "arr2[0]: " << arr2[0] << std::endl; // Вывод значения соответствующего элемента в arr2

    return 0;
}