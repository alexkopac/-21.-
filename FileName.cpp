#include <iostream>
#include <fstream>
#include <string>

class FileDisplay {
public:
    virtual void Display(const char* path) {
        std::ifstream file(path);  
        if (!file.is_open()) {
            std::cerr << "Не вдалося відкрити файл: " << path << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {  
            std::cout << line << std::endl;
        }

        file.close();
    }

    virtual ~FileDisplay() {}
};

class FileDisplayASCII : public FileDisplay {
public:
    void Display(const char* path) override {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Не вдалося відкрити файл: " << path << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            for (char ch : line) {
                std::cout << "ASCII код для символа '" << ch << "': " << static_cast<int>(ch) << std::endl;
            }
        }

        file.close();
    }
};

class FileDisplayBinary : public FileDisplay {
public:
    void Display(const char* path) override {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Не вдалося відкрити файл: " << path << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            for (char ch : line) {
                for (int i = 7; i >= 0; --i) {
                    std::cout << ((ch >> i) & 1);  
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        }

        file.close();
    }
};

int main() {
    

    const char* filePath = "example.txt";  

    FileDisplay file;  
    std::cout << "Вміст файлу (текст):" << std::endl;
    file.Display(filePath);
    std::cout << std::endl;

    FileDisplayASCII fileASCII;  
    std::cout << "Вміст файлу (ASCII-коди):" << std::endl;
    fileASCII.Display(filePath);
    std::cout << std::endl;

    FileDisplayBinary fileBinary;  
    std::cout << "Вміст файлу (Двійковий формат):" << std::endl;
    fileBinary.Display(filePath);

    return 0;
}
