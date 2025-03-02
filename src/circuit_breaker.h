//
// Created by Eddie Tsai on 2/21/25.
//

#ifndef CIRCUIT_BREAKER_H
#define CIRCUIT_BREAKER_H

#include "order_book.h"

class CircuitBreaker {
public:
    void check(const OrderBook &orderBook);
};

#endif //CIRCUIT_BREAKER_H
