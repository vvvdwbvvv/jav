//
// Created by Eddie Tsai on 2/21/25.
//

#include "circuit_breaker.h"
#include <iostream>

void CircuitBreaker::check(const OrderBook &orderBook) {
    if (orderBook.bids.rbegin()->first - orderBook.asks.begin()->first > 10) {
        std::cout << "Circuit Breaker Triggered!" << std::endl;
    }
}
