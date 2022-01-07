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
                        votes[0] = (compute_kernel(x,  -0.01, -0.0, -0.01, -0.72, 0.14, -0.25, 0.09, -0.63, -0.24, -0.01, -0.71, -0.26, -0.94, -0.04, -0.97, 0.36, 0.03, 0.3, 1.05, 0.24, 0.32, 0.56, 0.14, 0.38, -0.08, 0.14, -0.07, -0.13, 0.53, -0.4, -0.12, -0.25, -0.29, -0.05, -0.48, -0.55, 0.89, -0.28, 0.63, 0.41, 0.25, 0.34, -0.07, -0.45, -0.51) - 0.670539205427 ) * -9.526540752525 + -0.218534339836;
                        votes[1] = (compute_kernel(x,  0.0, -0.03, -0.0, 0.8, 0.17, -0.4, -1.14, 0.44, -0.13, -0.78, 0.42, -0.08, 1.96, -0.09, 0.09, -0.34, 0.23, 0.0, -2.14, 0.37, -0.2, 0.05, 1.27, 0.0, -0.4, 0.5, -0.03, -0.33, -1.38, -0.02, 0.34, 0.17, 0.03, 1.85, 3.09, 0.13, 0.3, -1.34, 0.04, 0.73, -2.41, 0.06, 1.0, -0.8, 0.06) - 0.53073234317 ) * -16.547577133781 + -3.4137504763;
                        votes[2] = (compute_kernel(x,  10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0) - 0.045454545455 ) * 10.737419307344 + -6.412059319762;
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

                        return exp(-0.01 * kernel);
                    }
                };
            }
        }
    }