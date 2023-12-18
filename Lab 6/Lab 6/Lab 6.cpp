#include <iostream>
#include <string>
#include <vector>

class CipherStrategy {
public:
    virtual std::string Process(const std::string& input, const std::string& key) = 0;
};

class EncryptStrategy : public CipherStrategy {
public:
    std::string Process(const std::string& input, const std::string& key) override {
        std::string result = input;
        for (size_t i = 0; i < input.size(); i++) {
            result[i] = input[i] ^ key[i % key.size()];
        }
        return result;
    }
};

class DecryptStrategy : public CipherStrategy {
public:
    std::string Process(const std::string& input, const std::string& key) override {
        return EncryptStrategy().Process(input, key);
    }
};

class XORCipher {
public:
    XORCipher() : strategy(nullptr) {}

    void SetStrategy(CipherStrategy* newStrategy) {
        strategy = newStrategy;
    }

    std::string Process(const std::string& input, const std::string& key) {
        if (strategy) {
            return strategy->Process(input, key);
        }
        return "";
    }

private:
    CipherStrategy* strategy;
};

int main() {

    setlocale(LC_ALL, "Russian");

    std::string plaintext = "Hello, XOR Cipher!";
    std::string key = "SecretKey";

    XORCipher cipher;

    // Шифрование
    cipher.SetStrategy(new EncryptStrategy);
    std::string encryptedText = cipher.Process(plaintext, key);

    // Дешифрование
    cipher.SetStrategy(new  DecryptStrategy);
    std::string decryptedText = cipher.Process(encryptedText, key);

    std::cout << "Исходный текст: " << plaintext << std::endl;
    std::cout << "Шифрованный текст: " << encryptedText << std::endl;
    std::cout << "Дешифрованный текст: " << decryptedText << std::endl;

    return 0;
}
