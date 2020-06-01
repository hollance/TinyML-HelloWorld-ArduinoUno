#include <math.h>
#include "model.h"
#include "model_data.h"

inline float relu(float x) {
    return fmaxf(0.0f, x); 
}

float predict(float x) {
    // The activations of the first layer are small enough to store
    // on the stack (16 floats = 64 bytes).
    float h1[DENSE1_SIZE];

    // First dense layer. Since there is only one input neuron, we don't need 
    // to perform a full-blown matrix multiply.
    for (int i = 0; i < DENSE1_SIZE; ++i) {
        h1[i] = relu(x * W1(i) + b1(i));
    }

    // Second dense layer.
    float y(0.0f);
    for (int i = 0; i < DENSE2_SIZE; ++i) {
        // Perform a dot product of the incoming activation vector with each 
        // row of the W2 matrix.
        float h2(0.0f);
        for (int j = 0; j < DENSE1_SIZE; ++j) {
            h2 += h1[j] * W2(i, j);
        }
        h2 = relu(h2 + b2(i));

        // We don't actually need to store the activations of the second layer. 
        // Since the last layer only has one neuron, we can immediately compute 
        // how much each activation contributes to the final layer.
        y += h2 * W3(i);
    }

    // Final dense layer.
    return y + b3();
}
