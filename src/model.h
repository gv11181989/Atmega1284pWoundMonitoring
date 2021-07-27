#pragma once
#include <stdarg.h>
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
                        votes[0] = (compute_kernel(x,  0.0, -0.0, -0.01, -0.0, -0.0, 0.0, -0.0, -0.01, -0.01, -0.01, -0.0, 0.0, -0.01, -0.0, -0.01, 0.01, -0.0, 0.0, 0.0, -0.0, 0.0, 0.01, -0.0, 0.0, 0.0, -0.0, 0.01, -0.01, -0.0, -0.0, -0.01, 0.0, -0.0, -0.0, 0.0, -0.0, -0.0, 0.01, -0.0, -0.0, 0.01, 0.0, -0.0, 0.01, 0.0) - 0.39274447252 ) * -10.140309019723 + -2.265079412947;
                        votes[1] = (compute_kernel(x,  0.0, -0.0, -0.01, -0.0, -0.0, 0.0, -0.0, -0.01, -0.01, -0.01, -0.0, 0.0, -0.01, -0.0, -0.01, 0.01, -0.0, 0.0, 0.0, -0.0, 0.0, 0.01, -0.0, 0.0, 0.0, -0.0, 0.01, -0.01, -0.0, -0.0, -0.01, 0.0, -0.0, -0.0, 0.0, -0.0, -0.0, 0.01, -0.0, -0.0, 0.01, 0.0, -0.0, 0.01, 0.0) - 0.39274447252 ) * 5.526396918676 + 2.383392782773;
                        votes[2] = (compute_kernel(x,  -0.01, -0.0, -0.01, -0.72, 0.14, -0.25, 0.09, -0.63, -0.24, -0.01, -0.71, -0.26, -0.94, -0.04, -0.97, 0.36, 0.03, 0.3, 1.05, 0.24, 0.32, 0.56, 0.14, 0.38, -0.08, 0.14, -0.07, -0.13, 0.53, -0.4, -0.12, -0.25, -0.29, -0.05, -0.48, -0.55, 0.89, -0.28, 0.63, 0.41, 0.25, 0.34, -0.07, -0.45, -0.51) - 0.206775856501 ) * -2.578989811635 + -6.020017571344;
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
