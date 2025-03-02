//
// Created by Eddie Tsai on 2/21/25.
//

#ifndef CONFIG_H
#define CONFIG_H

const std::string KAFKA_BROKER = "localhost:9092";
const std::string KAFKA_TOPIC = "order_book";

const double LIQUIDITY_THRESHOLD = -0.3;
const double VOLATILITY_THRESHOLD = 0.5;

#endif
