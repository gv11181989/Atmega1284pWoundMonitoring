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
                        votes[0] = (compute_kernel(x,  0.0, -0.0, -0.01, -0.0, -0.0, 0.0, -0.0, -0.01, -0.01, -0.01, -0.0, 0.0, -0.01, -0.0, -0.01, 0.01, -0.0, 0.0, 0.0, -0.0, 0.0, 0.01, -0.0, 0.0, 0.0, -0.0, 0.01, -0.01, -0.0, -0.0, -0.01, 0.0, -0.0, -0.0, 0.0, -0.0, -0.0, 0.01, -0.0, -0.0, 0.01, 0.0, -0.0, 0.01, 0.0) - 0.36458159149 ) * -11.194181731969 + -2.264447829288;
                        votes[1] = (compute_kernel(x,  0.0, -0.0, -0.01, -0.0, -0.0, 0.0, -0.0, -0.01, -0.01, -0.01, -0.0, 0.0, -0.01, -0.0, -0.01, 0.01, -0.0, 0.0, 0.0, -0.0, 0.0, 0.01, -0.0, 0.0, 0.0, -0.0, 0.01, -0.01, -0.0, -0.0, -0.01, 0.0, -0.0, -0.0, 0.0, -0.0, -0.0, 0.01, -0.0, -0.0, 0.01, 0.0, -0.0, 0.01, 0.0) - 0.36458159149 ) * 11.740684268017 + 2.869813763637;
                        votes[2] = (compute_kernel(x,  10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0) - 0.045454545455 ) * 10.756329651502 + -6.442520147038;
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

                        return exp(-0.1 * kernel);
                    }
                };
            }
        }
    }