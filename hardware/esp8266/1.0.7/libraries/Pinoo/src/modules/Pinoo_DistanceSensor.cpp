/**
 * @file Pinoo_DistanceSensor.cpp
 * @brief HC-SR04 Ultrasonic Distance Sensor source implementation.
 * 
 * @author Semih Aydın <semih@mobilitysoftware.net>
 * @copyright Copyright (c) 2026 Pinoo Robotics & Mobility Software
 */

#include "Pinoo_DistanceSensor.h"

Pinoo_DistanceSensor::Pinoo_DistanceSensor(uint8_t trigPin, uint8_t echoPin) 
    : _trigPin(trigPin), _echoPin(echoPin) {}

void Pinoo_DistanceSensor::begin() {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    digitalWrite(_trigPin, LOW);
}

float Pinoo_DistanceSensor::getDistance() {
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    long duration = pulseIn(_echoPin, HIGH, 30000);

    if (duration == 0) {
        return -1.0f;
    }

    return (float)duration * 0.01715f;
}
