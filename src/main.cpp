//
// Created by Eddie Tsai on 2/21/25.
//
#include <iostream>
#include <string>
#include "kafka_consumer.h"
#include "risk_engine.h"
#include "order_book.h"
#include "circuit_breaker.h"
#include "position_manager.h"
#include <nlohmann/json.hpp>

int main() {
    KafkaConsumer consumer("localhost:9092", "order-book");
    RiskEngine riskEngine;
    CircuitBreaker circuitBreaker;
    PositionManager positionManager;

    std::cout << "開始消費 Kafka 訊息..." << std::endl;
    while (true) {
        std::string message = consumer.consume();
        if (!message.empty()) {
            std::cout << "收到 Kafka 訊息: " << message << std::endl;
            OrderBook orderBook = parse_order_book(message);
            riskEngine.evaluate(orderBook);
            circuitBreaker.check(orderBook);
            positionManager.update(orderBook);
        }
    }
    return 0;
}
