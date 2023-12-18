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

    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Push element to queue\n";
        std::cout << "2. Pop element from queue\n";
        std::cout << "3. Front element\n";
        std::cout << "4. Back element\n";
        std::cout << "5. Queue size\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            std::cout << "Enter element to push: ";
            std::cin >> value;
            queue.push(value);
            std::cout << "Element " << value << " pushed to queue.\n";
            break;
        }
        case 2: {
            if (queue.isEmpty()) {
                std::cout << "Queue is empty.\n";
            }
            else {
                int frontElement = queue.front();
                queue.pop();
                std::cout << "Element " << frontElement << " popped from queue.\n";
            }
            break;
        }
        case 3: {
            if (queue.isEmpty()) {
                std::cout << "Queue is empty.\n";
            }
            else {
                std::cout << "Front element: " << queue.front() << std::endl;
            }
            break;
        }
        case 4: {
            if (queue.isEmpty()) {
                std::cout << "Queue is empty.\n";
            }
            else {
                std::cout << "Back element: " << queue.back() << std::endl;
            }
            break;
        }
        case 5: {
            std::cout << "Queue size: " << queue.size() << std::endl;
            break;
        }
        case 6: {
            std::cout << "Exiting...\n";
            return 0;
        }
        default: {
            std::cout << "Invalid choice. Try again.\n";
            break;
        }
        }

        std::cout << std::endl;
    }

    return 0;
}
