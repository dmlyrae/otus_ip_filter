#include <gtest/gtest.h>
#include "ip_address.h"
#include "ip_filter.h"
#include <vector>
#include <sstream>
#include <algorithm>

// тест на конструктор
TEST(IpAddressTest, Constructor) {
    IpAddress ip(192, 168, 1, 1);
    EXPECT_EQ(ip.octets[0], 192);
    EXPECT_EQ(ip.octets[1], 168);
    EXPECT_EQ(ip.octets[2], 1);
    EXPECT_EQ(ip.octets[3], 1);
}

// тест сравнения для сортировки
// 1.10.1.1 > 1.2.1.1
// 1.2.1.1 > 1.1.1.1
TEST(IpAddressTest, Comparison) {
    IpAddress ip1(1, 1, 1, 1);
    IpAddress ip2(1, 2, 1, 1);
    IpAddress ip3(1, 10, 1, 1);
    
    EXPECT_TRUE(ip3 < ip2);
    EXPECT_TRUE(ip2 < ip1);
    EXPECT_FALSE(ip1 < ip3);
}

// тесты для парсинга адресов
TEST(ParseIpTest, ValidAddress) {
    IpAddress ip = parseIp("192.168.1.1");
    EXPECT_EQ(ip.octets[0], 192);
    EXPECT_EQ(ip.octets[1], 168);
    EXPECT_EQ(ip.octets[2], 1);
    EXPECT_EQ(ip.octets[3], 1);
}

// тест для сортировки
TEST(SortTest, ReverseLexicographic) {
    std::vector<IpAddress> ipPool = {
        IpAddress(1, 1, 1, 1),
        IpAddress(1, 2, 1, 1),
        IpAddress(1, 10, 1, 1),
        IpAddress(46, 70, 1, 1)
    };
    
    std::sort(ipPool.begin(), ipPool.end());
    
    // ожидаемый: 
    // 46.70.1.1
    // 1.10.1.1 
    // 1.2.1.1 
    // 1.1.1.1
    EXPECT_EQ(ipPool[0].octets[0], 46);
    EXPECT_EQ(ipPool[0].octets[1], 70);
    EXPECT_EQ(ipPool[1].octets[0], 1);
    EXPECT_EQ(ipPool[1].octets[1], 10);
    EXPECT_EQ(ipPool[2].octets[0], 1);
    EXPECT_EQ(ipPool[2].octets[1], 2);
    EXPECT_EQ(ipPool[3].octets[0], 1);
    EXPECT_EQ(ipPool[3].octets[1], 1);
}

// тесты для variadic-template
TEST(FilterTest, SingleOctet) {
    std::vector<IpAddress> ipPool = {
        IpAddress(1, 1, 1, 1),
        IpAddress(2, 2, 2, 2),
        IpAddress(1, 2, 3, 4),
        IpAddress(10, 10, 10, 10)
    };
    
    std::sort(ipPool.begin(), ipPool.end());
    
    // по первому октету = 1
    // вход: 1.1.1.1, 1.2.3.4, 2.2.2.2
    // выход: 1.2.3.4, 1.1.1.1, 2.2.2.2
    std::ostringstream oss;
    auto old_cout = std::cout.rdbuf(oss.rdbuf());
    
    filter(ipPool, 1);
    
    std::cout.rdbuf(old_cout);
    std::string output = oss.str();
    
    EXPECT_TRUE(output.find("1.2.3.4") != std::string::npos);
    EXPECT_TRUE(output.find("1.1.1.1") != std::string::npos);
    EXPECT_TRUE(output.find("2.2.2.2") == std::string::npos);
}

TEST(FilterTest, TwoOctets) {
    std::vector<IpAddress> ipPool = {
        IpAddress(46, 70, 1, 1),
        IpAddress(46, 70, 2, 2),
        IpAddress(46, 71, 1, 1),
        IpAddress(47, 70, 1, 1)
    };
    
    std::sort(ipPool.begin(), ipPool.end());
    
    // по первому и второму октету = 46, 70
    // вход: 46.70.1.1, 46.70.2.2, 46.71.1.1, 47.70.1.1
    // выход: 46.70.2.2, 46.70.1.1, 47.70.1.1
    std::ostringstream oss;
    auto old_cout = std::cout.rdbuf(oss.rdbuf());
    
    filter(ipPool, 46, 70);
    
    std::cout.rdbuf(old_cout);
    std::string output = oss.str();
    
    // Проверяем, что выводятся только адреса 46.70.x.x
    EXPECT_TRUE(output.find("46.70.2.2") != std::string::npos);
    EXPECT_TRUE(output.find("46.70.1.1") != std::string::npos);
    EXPECT_TRUE(output.find("46.71.1.1") == std::string::npos);
    EXPECT_TRUE(output.find("47.70.1.1") == std::string::npos);
}
