#ifndef SIGNAL_PROCESSING_H
#define SIGNAL_PROCESSING_H

#define MAX_VALID_DISTANCE 400.0
#define MIN_VALID_DISTANCE 2.0
#define NOISE_THRESHOLD 50.0

float removeSaltPepperNoise(float distance, float lastValid);
float weightedMovingAverage(float *buffer, int size);
float saturateValue(float value, float minVal, float maxVal);

#endif
