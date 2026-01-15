#pragma once

#include <vector>
#include "ip_address.h"

/**
 * @brief Сборник фильтров в одну функцию.
 * 
 * реализует паттерн стратегия
 * принимает функцию-предикат, которая определяет условие фильтрации
 * 
 * @param ipPool вектор адресов для фильтрации
 * @param predicate указатель (!) на предикат
 */
void filterIpAddresses(const std::vector<IpAddress>& ipPool, 
                       bool (*predicate)(const IpAddress&));

/**
 * @brief Обработка ip-адресов: сортировка и применение фильтров
 * 
 * сортирует адреса в обратном порядке, выводит:
 * 1. все отсортированные адреса
 * 2. адреса с первым октетом = 1
 * 3. адреса с первым октетом = 46 и вторым = 70
 * 4. адреса, содержащие октет = 46
 * 
 * @param ipPool вектор адресов для обработки
 */
void processIpAddresses(std::vector<IpAddress>& ipPool);

