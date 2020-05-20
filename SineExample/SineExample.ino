#include "model.h"

const int LED_PIN = 11;

int inference_count = 0;
const int kInferencesPerCycle = 1000;
const float kXrange = 2.f * 3.14159265359f;

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    float position = static_cast<float>(inference_count) /
                     static_cast<float>(kInferencesPerCycle);
    float x_val = position * kXrange;

    float y_val = predict(x_val);

    // The model may actually predict values smaller than -1 or larger 
    // than 1, so clamp the results.
    y_val = constrain(y_val, -1.0f, 1.0f);

    // Calculate the brightness of the LED such that y=-1 is fully off 
    // and y=1 is fully on. The LED's brightness can range from 0-255.
    int brightness = (int)(127.5f * (y_val + 1.0f));

    analogWrite(LED_PIN, brightness);

    // Enable this to view the sine wave with the Serial Plotter.
    //Serial.println(brightness);

    inference_count += 1;
    if (inference_count >= kInferencesPerCycle) inference_count = 0;
}
