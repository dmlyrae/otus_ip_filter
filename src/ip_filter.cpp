/**
 * @file ip_filter.cpp
 * @brief Реализация функций фильтрации адресов через variadic-templates
 */

#include "ip_filter.h"
#include <algorithm>

// ============================================================================
// ФИЛЬТРАЦИЯ ПО ЛЮБОМУ ОКТЕТУ
// ============================================================================

/**
 * @brief Фильтрация адресов, содержащих указанное значение в любом октете
 * 
 * проверяет октеты адреса, возвращает true, если хотя бы один равен
 * 
 * @param ipPool Вектор IP-адресов для фильтрации
 * @param value Значение для поиска в любом из октетов
 */
void filter_any(const std::vector<IpAddress>& ipPool, uint8_t value) {
    for (const auto& ip : ipPool) {
        if (ip.contains(value)) {
            std::cout << ip << '\n';
        }
    }
}

// ============================================================================
// ОСНОВНАЯ ОБРАБОТКА
// ============================================================================

/**
 * @brief Обработка IP-адресов: сортировка и применение фильтров
 * 
 * Алгоритм:
 * 1. Проверяем, что пул не пуст
 * 2. Сортируем адреса в обратном лексикографическом
 * 3. Выводим адреса
 * 4. Применяем фильтры по заданию:
 *    - filter(ipPool, 1)
 *    - filter(ipPool, 46, 70)
 *    - filter_any(ipPool, 46)
 * 
 * @param ipPool Вектор IP-адресов для обработки
 */
void processIpAddresses(std::vector<IpAddress>& ipPool) {
    if (ipPool.empty()) {
        std::cout << "Нет IP-адресов для обработки.\n";
        return;
    }
    
    std::sort(ipPool.begin(), ipPool.end());
    
    for (const auto& ip : ipPool) {
        std::cout << ip << '\n';
    }
    
    filter(ipPool, 1);
    filter(ipPool, 46, 70);
    filter_any(ipPool, 46);
}
