#include <gtest/gtest.h>
#include "ip_address.h"
#include "ip_filter.h"
#include <vector>
#include <sstream>

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

