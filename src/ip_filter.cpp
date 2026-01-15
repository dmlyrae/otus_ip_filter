/**
 * @file ip_filter.cpp
 * @brief Реализация функций фильтрации ip-адресов.
 * 
 * Комбинация отдельных паттернов в одну функцию фильтрации через паттерн strategy.
 * https://en.wikipedia.org/wiki/Strategy_pattern
 */

#include "ip_filter.h"
#include <algorithm>
#include <iostream>

// ============================================================================
// СБОРЩИК ФИЛЬТРОВ
// ============================================================================

/**
 * @brief Сборищик фильтров в одну функцию.
 * 
 * реализует паттерн стратегия
 * принимает функцию-предикат, которая определяет условие фильтрации
 * 
 * @param ipPool вектор адресов (предполагается, что отсортирован)
 * @param predicate указатель (!) на предикат
 * предикат должен возвращать труе, если адрес проходит
 * 
 */
void filterIpAddresses(const std::vector<IpAddress>& ipPool, 
    bool (*predicate)(const IpAddress&)) {
    for (const auto& ip : ipPool) {
        if (predicate(ip)) {
            std::cout << ip << '\n';
        }
    }
}

// ============================================================================
// ПРЕДИКАТЫ ДЛЯ ФИЛЬТРАЦИИ
// ============================================================================

/**
 * @brief Предикат: проверяет, равен ли первый октет единице
 * 
 * Используется для фильтрации адресов вида 1.x.x.x
 */
static bool firstOctetIsOne(const IpAddress& ip) {
    return ip.octetEquals(0, 1);
}

/**
 * @brief Предикат для таска: проверяет, равен ли первый октет 46, а второй 70 
 * 
 * используется для фильтрации адресов вида 46.70.x.x
 */
static bool first46Second70(const IpAddress& ip) {
    return ip.octetEquals(0, 46) && ip.octetEquals(1, 70);
}

/**
 * @brief Предикат для таска: проверяет, содержит ли адрес октет со значением 46
 */
static bool contains46(const IpAddress& ip) {
    return ip.contains(46);
}

// ============================================================================
// ОСНОВНАЯ ОБРАБОТКА
// ============================================================================

/**
 * @brief Обработка IP-адресов: сортировка и применение фильтров
 * 
 * алгоритм:
 * 1. проверяем, что пул не пуст
 * 2. Сортируем адреса в обратном лексик
 * 3. выводим все
 * 4. применяем три фильтра последовательно через filterIpAddresses
 * 
 * @param ipPool вектор адресов для обработки
 */
void processIpAddresses(std::vector<IpAddress>& ipPool) {
    if (ipPool.empty()) {
        std::cout << "Нет IP-адресов для обработки.\n";
        return;
    }
    
    // сортировка в обратном лексикографическом
    // через оператор < структуры IpAddress
    std::sort(ipPool.begin(), ipPool.end());
    
    // Вывод
    for (const auto& ip : ipPool) {
        std::cout << ip << '\n';
    }
    //////////////////////////////////////////////////////////////
    
    filterIpAddresses(ipPool, firstOctetIsOne);
    filterIpAddresses(ipPool, first46Second70);
    filterIpAddresses(ipPool, contains46);
}

