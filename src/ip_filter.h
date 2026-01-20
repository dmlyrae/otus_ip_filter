#pragma once

#include <vector>
#include <iostream>
#include "ip_address.h"

// ============================================================================
// ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ ДЛЯ ПРОВЕРКИ ОКТЕТОВ
// ============================================================================

/**
 * @brief Функция для проверки соответствия октетов значениям
 * 
 * Рекурсивно проверяет variadic-параметры
 * 
 * @param ip ip-адрес для проверки
 * @param idx текущий индекс октета (начинается с 0)
 * @param first первое значение для проверки
 * @param rest variadic
 * @return boolean (1 если все октеты соответствуют значениям, 0 в противном случае)
 */
template<typename First, typename... Rest>
bool checkOctets(const IpAddress& ip, int idx, First first, Rest... rest) {
    // текущий октет
    if (!ip.octetEquals(idx, static_cast<uint8_t>(first))) {
        // не совпадает с заданным значением
        return false;
    }
    
    // рекурсивно следующий
    if constexpr (sizeof...(rest) > 0) {
        return checkOctets(ip, idx + 1, rest...);
    }
    // все октеты не не совпали
    return true;
}

/**
 * @brief Базовый случай рекурсии: остался один аргумент
 * 
 * @tparam First 
 * @param ip 
 * @param idx 
 * @param first 
 * @return true 
 * @return false 
 */
template<typename First>
bool checkOctets(const IpAddress& ip, int idx, First first) {
    return ip.octetEquals(idx, static_cast<uint8_t>(first));
}

// ============================================================================
// ОСНОВНАЯ ФУНКЦИЯ ФИЛЬТРАЦИИ (VARIADIC TEMPLATE)
// ============================================================================

/**
 * @brief Универсальная функция фильтрации адресов через variadic template
 * 
 * Фильтрует адреса, у которых октеты на указанных позициях равны заданным значениям.

 * @param ipPool вектор адресов для фильтрации (отсортированный)
 * @param args variadic-параметры -- значения для проверки по позициям
 */
template<typename... Args>
void filter(const std::vector<IpAddress>& ipPool, Args... args) {
    // для проверки нужно не более 4 и не менее1 
    static_assert(sizeof...(args) <= 4, "Too many arguments for IP address (max 4 octets)");
    static_assert(sizeof...(args) > 0, "At least one argument required");
    
    for (const auto& ip : ipPool) {
        if (checkOctets(ip, 0, args...)) {
            std::cout << ip << '\n';
        }
    }
}

/**
 * @brief Фильтрация адресов, содержащих значение в any октете
 * 
 * проверяет 4 октета адреса, возвращает true, если хотя бы один
 * 
 * @param ipPool Вектор IP-адресов для фильтрации
 * @param value Значение для поиска в любом из 4 октетов
 */
void filter_any(const std::vector<IpAddress>& ipPool, uint8_t value);

/**
 * @brief Обработка адресов: сортировка и применение фильтров по таску из homework
 * 
 * Сортирует адреса в обратном лексикографическом порядке и выводит:
 * 1. Все отсортированные адреса
 * 2. Адреса с первым октетом = 1
 * 3. Адреса с первым октетом = 46 и вторым = 70
 * 4. Адреса, содержащие октет = 46
 * 
 * @param ipPool Вектор IP-адресов для обработки
 */
void processIpAddresses(std::vector<IpAddress>& ipPool);
