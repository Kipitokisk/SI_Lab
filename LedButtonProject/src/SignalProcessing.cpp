#include "SignalProcessing.h"

float removeSaltPepperNoise(float distance, float lastValid) {
    if ((distance - lastValid > NOISE_THRESHOLD) || (lastValid - distance > NOISE_THRESHOLD)) {
        return lastValid;
    }
    return distance;
}

float weightedMovingAverage(float *buffer, int size) {
    float sum = 0;
    float weightSum = 0;
    for (int i = 0; i < size; i++) {
        float weight = i + 1;
        sum += buffer[i] * weight;
        weightSum += weight;
    }
    return sum / weightSum;
}

float saturateValue(float value, float minVal, float maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}
