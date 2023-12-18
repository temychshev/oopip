#include <iostream>

template<typename T>
class ShPtrArr {
public:
    ShPtrArr(T* arr = nullptr)
        : m_arr(arr)
        , m_refCount(new int(1))
    {
    }

    ShPtrArr(const ShPtrArr<T>& other)
        : m_arr(other.m_arr)
        , m_refCount(other.m_refCount)
    {
        (*m_refCount)++;
    }

    ~ShPtrArr()
    {
        (*m_refCount)--;
        if (*m_refCount == 0) {
            delete[] m_arr;
            delete m_refCount;
        }
    }

    ShPtrArr<T>& operator=(const ShPtrArr<T>& other)
    {
        if (this != &other) {
            (*m_refCount)--;
            if (*m_refCount == 0) {
                delete[] m_arr;
                delete m_refCount;
            }

            m_arr = other.m_arr;
            m_refCount = other.m_refCount;
            (*m_refCount)++;
        }
        return *this;
    }

    T& operator[](int index)
    {
        return m_arr[index];
    }

private:
    T* m_arr;
    int* m_refCount;
};

int main()
{
    int arrSize = 5;
    ShPtrArr<int> arr(new int[arrSize]);

    for (int i = 0; i < arrSize; i++) {
        arr[i] = i;
    }

    // Проверка метода оператора []
    std::cout << "Array elements: ";
    for (int i = 0; i < arrSize; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Проверка создания копии массива
    ShPtrArr<int> arrCopy(arr);
    std::cout << "Copied array elements: ";
    for (int i = 0; i < arrSize; i++) {
        std::cout << arrCopy[i] << " ";
    }
    std::cout << std::endl;

    // Проверка оператора присваивания
    ShPtrArr<int> arrAssigned;
    arrAssigned = arr;
    std::cout << "Assigned array elements: ";
    for (int i = 0; i < arrSize; i++) {
        std::cout << arrAssigned[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
