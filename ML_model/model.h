#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class RVC {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        float votes[1] = { 0 };
                        votes[0] = (compute_kernel(x,  -0.0, -0.0, 0.0, -0.0, -0.0, 0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, 0.0, 0.0, 0.0, -0.0, 0.02, -0.0, -0.0, 0.01, 0.0, 0.0, 0.0, -0.0, -0.0, 0.01, 0.0, 0.01, -0.0, 0.01, -0.01, -0.0, 0.01, -0.01, -0.0, 0.0, 0.01, -0.0, 0.0, 0.0, -0.0, 0.01, 0.01) - 0.969166593698 ) * 162.041511192396 + -0.60602882081;
                        // return argmax of votes
                        uint8_t classIdx = 0;
                        float maxVotes = votes[0];

                        for (uint8_t i = 1; i < 1; i++) {
                            if (votes[i] > maxVotes) {
                                classIdx = i;
                                maxVotes = votes[i];
                            }
                        }

                        return classIdx;
                    }

                protected:
                    /**
                    * Compute kernel between feature vector and support vector.
                    * Kernel type: rbf
                    */
                    float compute_kernel(float *x, ...) {
                        va_list w;
                        va_start(w, 45);
                        float kernel = 0.0;

                        for (uint16_t i = 0; i < 45; i++) {
                            kernel += pow(x[i] - va_arg(w, double), 2);
                        }

                        return exp(-0.001 * kernel);
                    }
                };
            }
        }
    }