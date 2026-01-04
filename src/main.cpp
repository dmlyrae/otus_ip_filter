#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "lib.h"

/**
 * @brief Структура IP-адреса
 */
struct IpAddress {
    uint8_t octets[4];  ///< Октеты адреса

    IpAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d) 
        : octets{a, b, c, d} {}
    
    /**
     * @brief Сравнение для сортировки по убыванию (обратный лексикографический порядок)
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator<(const IpAddress& other) const {
        for (int i = 0; i < 4; ++i) {
            if (octets[i] != other.octets[i]) {
                return octets[i] > other.octets[i];
            }
        }
        return false;
    }
    
    // Проверка, равен ли октет под номером idx значению value
    bool octetEquals(int idx, uint8_t value) const {
        return octets[idx] == value;
    }
    
    // Проверка, содержит ли адрес октет со значением value
    bool contains(uint8_t value) const {
        for (int i = 0; i < 4; ++i) {
            if (octets[i] == value) return true;
        }
        return false;
    }
};

// --- Вспомогательные функции ---

// вывод ip-адреса в поток
std::ostream& operator<<(std::ostream& os, const IpAddress& ip) {
    os << static_cast<int>(ip.octets[0]) << "."
       << static_cast<int>(ip.octets[1]) << "."
       << static_cast<int>(ip.octets[2]) << "."
       << static_cast<int>(ip.octets[3]);
    return os;
}

// парсинг IP-адреса из строки вида "a.b.c.d"
IpAddress parseIp(const std::string& ipStr) {
    std::istringstream stream(ipStr);
    std::string part;
    uint8_t octets[4];
    int idx = 0;
    
    while (std::getline(stream, part, '.') && idx < 4) {
        octets[idx++] = static_cast<uint8_t>(std::stoi(part));
    }
    
    if (idx != 4) {
        throw std::invalid_argument("Неверный формат IP-адреса: " + ipStr);
    }
    
    return IpAddress(octets[0], octets[1], octets[2], octets[3]);
}

// Извлечение первого столбца из строки (разделенной табуляцией)
std::string extractFirstColumn(const std::string& line) {
    size_t tabPos = line.find('\t');
    if (tabPos != std::string::npos) {
        return line.substr(0, tabPos);
    }
    return line;
}

// --- Фильтры ---

/**
 * @brief 
 * 
 * @param ipPool 
 */
void filterFirstOctetIsOne(const std::vector<IpAddress>& ipPool) {
    // std::cout << "\nАдреса с первым октетом 1:\n";
    for (const auto& ip : ipPool) {
        if (ip.octetEquals(0, 1)) {
            std::cout << ip << '\n';
        }
    }
}

/**
 * @brief 
 * 
 * @param ipPool 
 */
void filterFirst46Second70(const std::vector<IpAddress>& ipPool) {
    for (const auto& ip : ipPool) {
        if (ip.octetEquals(0, 46) && ip.octetEquals(1, 70)) {
            std::cout << ip << '\n';
        }
    }
}

/**
 * @brief 
 * 
 * @param ipPool 
 */
void filterContains46(const std::vector<IpAddress>& ipPool) {
    for (const auto& ip : ipPool) {
        if (ip.contains(46)) {
            std::cout << ip << '\n';
        }
    }
}

// --- Основная обработка ---
void processIpAddresses(std::vector<IpAddress>& ipPool) {
    if (ipPool.empty()) {
        std::cout << "Нет IP-адресов для обработки.\n";
        return;
    }
    
    // сортировка (по убыванию)
    std::sort(ipPool.begin(), ipPool.end());
    
    // Вывод всех отсортированных адресов
    for (const auto& ip : ipPool) {
        std::cout << ip << '\n';
    }
    
    // Применение фильтров
    filterFirstOctetIsOne(ipPool);
    filterFirst46Second70(ipPool);
    filterContains46(ipPool);
}

int main(int argc, char* argv[]) {
    // отработка аргумента --version
    // тест от template-repo
    if (argc > 1 && std::string(argv[1]) == "--version") {
        std::cout << "Version: " << get_version() << std::endl;
        return 0;
    }
    
    try {
        std::vector<IpAddress> ipPool;
        std::string line;
        
        // чтение данных из stdin
        // Проверяем, есть ли данные в stdin, чтобы не зависнуть
        if (argc == 1 && std::cin.peek() == std::char_traits<char>::eof()) {
            // stdin пустой, выводим версию для теста
            std::cout << "Version: " << get_version() << std::endl;
            return 0;
        }
        
        while (std::getline(std::cin, line)) {
            if (line.empty()) continue;
            
            std::string ipStr = extractFirstColumn(line);
            ipPool.push_back(parseIp(ipStr));
        }
        
        // данные не поступили, выводим версию для теста
        if (ipPool.empty() && argc == 1) {
            std::cout << "Version: " << get_version() << std::endl;
            return 0;
        }
        
        processIpAddresses(ipPool);
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}