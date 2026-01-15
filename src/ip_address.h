#pragma once

#include <cstdint>
#include <iosfwd>
#include <string>

/**
 * @brief Структура IP-адреса
 */
struct IpAddress {
    uint8_t octets[4];  ///< Октеты адреса

    IpAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d) 
        : octets{a, b, c, d} {}
    
    /**
     * @brief Сравнение для сортировки по убыванию (обратный лексикографический порядок)
     */
    bool operator<(const IpAddress& other) const;
    
    /**
     * @brief Проверка, равен ли октет под номером idx значению value
     */
    bool octetEquals(int idx, uint8_t value) const;
    
    /**
     * @brief Проверка, содержит ли адрес октет со значением value
     */
    bool contains(uint8_t value) const;
};

/**
 * @brief Вывод IP-адреса в поток
 */
std::ostream& operator<<(std::ostream& os, const IpAddress& ip);

/**
 * @brief Парсинг IP-адреса из строки вида "a.b.c.d"
 * @param ipStr Строка с IP-адресом
 * @return IpAddress
 * @throws std::invalid_argument если формат неверный
 */
IpAddress parseIp(const std::string& ipStr);

/**
 * @brief Извлечение первого столбца из строки (разделенной табуляцией)
 * @param line Строка с данными
 * @return Первый столбец до табуляции
 */
std::string extractFirstColumn(const std::string& line);

