#include <iostream>
#include <list>
#include <stdexcept>

// Custom exception class
class CustomException : public std::exception {
public:
    explicit CustomException(const char* message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

// Iterator class
template <typename T>
class Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator(typename std::list<T>::iterator iter, typename std::list<T>::iterator end, bool positive)
        : iter_(iter), end_(end), positive_(positive) {
        findNext();
    }

    Iterator& operator++() {
        ++iter_;
        findNext();
        return *this;
    }

    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const Iterator& other) const {
        return iter_ == other.iter_;
    }

    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }

    reference operator*() const {
        if (iter_ == end_) {
            throw CustomException("Attempt to dereference an invalid iterator.");
        }
        return *iter_;
    }

private:
    void findNext() {
        while (iter_ != end_) {
            if ((positive_ && *iter_ > 0) || (!positive_ && *iter_ < 0)) {
                break;
            }
            ++iter_;
        }
    }

    typename std::list<T>::iterator iter_;
    typename std::list<T>::iterator end_;
    bool positive_;
};

template <typename T>
class Queue {
public:
    Queue() {}

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

    Iterator<T> begin(bool positive = true) {
        return Iterator<T>(data_.begin(), data_.end(), positive);
    }

    Iterator<T> end() {
        return Iterator<T>(data_.end(), data_.end(), true);
    }

private:
    std::list<T> data_;
};

template <typename T>
void printElements(const Iterator<T>& begin, const Iterator<T>& end, const std::string& message) {
    std::cout << message;
    for (auto it = begin; it != end; ++it) {
        try {
            std::cout << *it << " ";
        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
    std::cout << std::endl;
}

int main() {
    Queue<int> queue;

    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Push element to queue\n";
        std::cout << "2. Pop element from queue\n";
        std::cout << "3. Front element\n";
        std::cout << "4. Back element\n";
        std::cout << "5. Queue size\n";
        std::cout << "6. Iterate positive elements\n";
        std::cout << "7. Iterate negative elements\n";
        std::cout << "8. Exit\n";
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
                queue.pop();
                std::cout << "Element popped from queue.\n";
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
            printElements(queue.begin(true), queue.end(), "Queue elements using positive iterators: ");
            break;
        }
        case 7: {
            printElements(queue.begin(false), queue.end(), "Queue elements using negative iterators: ");
            break;
        }
        case 8: {
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
