//
// Created by Eddie Tsai on 2/21/25.
//

#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <string>
#include <iostream>

class OrderBook {
public:
    double bidPrice = 0.0;
    double askPrice = 0.0;

    // 存放全部深度資料
    std::map<double, double> bids;  // Key: 價格, Value: 數量
    std::map<double, double> asks;

    void update(bool is_bid, double price, double size);
};

OrderBook parse_order_book(const std::string &message);

#endif //ORDER_BOOK_H
