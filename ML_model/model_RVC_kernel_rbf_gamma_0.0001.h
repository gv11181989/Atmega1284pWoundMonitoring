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
                        float votes[3] = { 0 };
                        votes[0] = -0.18251409125734044;
                        votes[1] = -0.00023122595405685635;
                        votes[2] = (compute_kernel(x,  -0.34, 0.01, -0.5, -2.53, -0.82, -0.49, 0.12, -0.13, -0.65, 0.92, 0.6, 0.35, -0.06, 0.51, -0.35, -0.68, -0.1, -0.9, -0.61, -0.98, -0.25, -1.06, -0.69, -1.76, -0.76, -0.61, -1.87, 0.9, 0.17, -0.04, -0.53, -0.37, -0.67, 2.43, 0.81, 3.33, -2.37, -1.07, -1.44, -1.01, -0.45, -0.3, 1.14, 0.06, 2.95) - 0.975004616365 ) * -28.918533772966 + -6.395011849156;
                        // return argmax of votes
                        uint8_t classIdx = 0;
                        float maxVotes = votes[0];

                        for (uint8_t i = 1; i < 3; i++) {
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

                        return exp(-0.0001 * kernel);
                    }
                };
            }
        }
    }