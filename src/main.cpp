#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "ip_address.h"
#include "ip_filter.h"

int main(int argc, char* argv[]) {
    try {
        std::vector<IpAddress> ipPool;
        std::string line;
        
        // чтение данных 
        while (std::getline(std::cin, line)) {
            if (line.empty()) continue;
            
            std::string ipStr = extractFirstColumn(line);
            ipPool.push_back(parseIp(ipStr));
        }
        
        if (ipPool.empty()) {
            return 0;
        }
        
        processIpAddresses(ipPool);
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
