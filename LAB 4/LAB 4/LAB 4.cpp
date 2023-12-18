#include <iostream>
#include <list>

template <typename T>
class Queue {
public:
    Queue() {}

    Queue(std::initializer_list<T> initList) : data_(initList) {}

    Queue(const Queue& other) : data_(other.data_) {}

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            data_ = other.data_;
        }
        return *this;
    }

    Queue(Queue&& other) noexcept : data_(std::move(other.data_)) {}

    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }

    void push(const T& value) {
        data_.push_back(value);
    }

    void pop() {
        if (!isEmpty()) {
            data_.pop_front();
        }
    }

    T& front() {
        return data_.front();
    }

    const T& front() const {
        return data_.front();
    }

    T& back() {
        return data_.back();
    }

    const T& back() const {
        return data_.back();
    }

    size_t size() const {
        return data_.size();
    }

    bool isEmpty() const {
        return data_.empty();
    }

private:
    std::list<T> data_;
};

int main() {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    std::cout << "Queue size: " << queue.size() << std::endl;
    std::cout << "Front element: " << queue.front() << std::endl;
    std::cout << "Back element: " << queue.back() << std::endl;

    queue.pop();

    std::cout << "After pop, Front element: " << queue.front() << std::endl;

    return 0;
}
