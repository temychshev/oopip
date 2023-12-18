#include <iostream>

template <typename T>
class ShPtrArr {
public:
    ShPtrArr() : data_(nullptr), refCount_(nullptr) {}

    explicit ShPtrArr(size_t size) : data_(new T[size]), refCount_(new size_t(1)), size_(size) {}

    ShPtrArr(const ShPtrArr& other) : data_(other.data_), refCount_(other.refCount_), size_(other.size_) {
        if (refCount_) {
            ++(*refCount_);
        }
    }

    ~ShPtrArr() {
        release();
    }

    ShPtrArr& operator=(const ShPtrArr& other) {
        if (this != &other) {
            release();
            data_ = other.data_;
            refCount_ = other.refCount_;
            size_ = other.size_;
            if (refCount_) {
                ++(*refCount_);
            }
        }
        return *this;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    size_t getSize() const {
        return size_;
    }

private:
    void release() {
        if (refCount_) {
            --(*refCount_);
            if (*refCount_ == 0) {
                delete[] data_;
                delete refCount_;
            }
        }
    }

    T* data_;
    size_t* refCount_;
    size_t size_;
};

int main() {
    ShPtrArr<int> arr1(5);
    for (size_t i = 0; i < arr1.getSize(); ++i) {
        arr1[i] = i + 1;
    }

    ShPtrArr<int> arr2 = arr1;
    arr2[0] = 10;

    std::cout << "arr1: ";
    for (size_t i = 0; i < arr1.getSize(); ++i) {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "arr2: ";
    for (size_t i = 0; i < arr2.getSize(); ++i) {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
