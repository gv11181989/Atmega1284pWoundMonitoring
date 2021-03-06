#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class SVM {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        float kernels[17] = { 0 };
                        float decisions[3] = { 0 };
                        int votes[3] = { 0 };
                        kernels[0] = compute_kernel(x,   0.0  , -0.03  , -0.0  , 0.8  , 0.17  , -0.4  , -1.14  , 0.44  , -0.13  , -0.78  , 0.42  , -0.08  , 1.96  , -0.09  , 0.09  , -0.34  , 0.23  , 0.0  , -2.14  , 0.37  , -0.2  , 0.05  , 1.27  , 0.0  , -0.4  , 0.5  , -0.03  , -0.33  , -1.38  , -0.02  , 0.34  , 0.17  , 0.03  , 1.85  , 3.09  , 0.13  , 0.3  , -1.34  , 0.04  , 0.73  , -2.41  , 0.06  , 1.0  , -0.8  , 0.06 );
                        kernels[1] = compute_kernel(x,   0.69  , -0.18  , 1.96  , 0.77  , -0.16  , 1.52  , -0.09  , -0.23  , 0.31  , -0.09  , -0.26  , -0.36  , 0.24  , 0.32  , 0.12  , 0.48  , -0.1  , 0.54  , 0.69  , -0.16  , 0.35  , 0.89  , -0.07  , -2.26  , -0.23  , 0.0  , -1.51  , 0.64  , -0.02  , -1.91  , 0.02  , -0.36  , 1.86  , 0.3  , -0.3  , -1.48  , 0.03  , -0.29  , -1.33  , -0.04  , -0.3  , -1.41  , 0.2  , -0.38  , -1.78 );
                        kernels[2] = compute_kernel(x,   -0.98  , 0.27  , 0.39  , -0.47  , 0.22  , -0.18  , -0.08  , 0.09  , 0.65  , 0.11  , -0.11  , 0.58  , 0.07  , -0.1  , 0.59  , 1.25  , -1.95  , -2.68  , -0.42  , 1.85  , 2.63  , -0.27  , 0.06  , 0.07  , 0.13  , -0.2  , -0.12  , -0.0  , 0.91  , 1.99  , -0.74  , 0.0  , 0.03  , -0.0  , -0.19  , -0.18  , -0.66  , -0.63  , -1.15  , -0.26  , 1.81  , 2.52  , 1.11  , -1.18  , -1.56 );
                        kernels[3] = compute_kernel(x,   -0.74  , 0.0  , 0.03  , -0.0  , -0.19  , -0.18  , -0.66  , -0.63  , -1.15  , -0.26  , 1.81  , 2.52  , 1.11  , -1.18  , -1.56  , -0.01  , -0.01  , -0.0  , -0.01  , 0.03  , 0.0  , -0.52  , 1.36  , 0.88  , -1.15  , 1.57  , 1.04  , -0.83  , -0.34  , -0.6  , -0.6  , 0.99  , 1.73  , -0.23  , 0.7  , 1.02  , 0.57  , -1.9  , -1.75  , -0.15  , -0.48  , -0.48  , 0.02  , 1.06  , 0.57 );
                        kernels[4] = compute_kernel(x,   0.37  , 0.3  , 0.37  , -0.77  , -0.62  , -1.04  , 1.32  , 0.03  , -0.71  , -1.31  , -0.3  , 0.3  , -0.27  , 0.08  , 1.89  , 0.46  , 0.08  , 0.55  , -2.05  , -0.51  , -2.74  , -0.61  , 0.16  , -1.76  , 0.17  , -0.2  , -3.72  , 0.07  , -0.35  , -0.11  , -0.02  , -0.07  , 0.24  , -0.11  , -0.01  , 0.25  , -1.64  , -0.33  , -2.13  , 0.62  , 0.33  , -2.21  , 1.4  , 0.06  , -4.63 );
                        kernels[5] = compute_kernel(x,   0.12  , 0.15  , 2.97  , -0.08  , 0.57  , 1.49  , 0.12  , -0.02  , -0.09  , 0.11  , -0.2  , -1.46  , 0.62  , 0.02  , -0.76  , 3.08  , 0.4  , -0.02  , 0.87  , 0.23  , 0.51  , 1.44  , 0.18  , 0.6  , 2.53  , 0.08  , 0.26  , 2.43  , 0.17  , -0.07  , 0.13  , 0.06  , 0.04  , 2.8  , 1.86  , 2.83  , -1.84  , -0.25  , -0.48  , -1.99  , 0.24  , -0.4  , 3.17  , 1.34  , 1.71 );
                        kernels[6] = compute_kernel(x,   -1.64  , -0.86  , -1.6  , -2.6  , -0.81  , -1.48  , -0.06  , 0.2  , -0.36  , -0.18  , -0.25  , -0.55  , 1.57  , 1.18  , 1.56  , -0.98  , -0.8  , -0.4  , 2.6  , 0.84  , 2.06  , -0.65  , -0.65  , -2.03  , -0.02  , -0.48  , -1.85  , 0.86  , 0.16  , 0.47  , 1.13  , 0.66  , 1.96  , -0.82  , -0.9  , -2.41  , 0.89  , 0.81  , 2.49  , 1.32  , 0.65  , 2.85  , 0.28  , -0.12  , 0.1 );
                        kernels[7] = compute_kernel(x,   -0.77  , -0.13  , -1.91  , -0.13  , 0.86  , 0.18  , -0.38  , -0.02  , -1.63  , -0.4  , -0.2  , -2.1  , -0.19  , 0.32  , -0.13  , 0.58  , 0.69  , 2.76  , 0.8  , 1.5  , 2.73  , -1.98  , -0.17  , -2.27  , 0.4  , 1.27  , 2.08  , -1.2  , 0.08  , -0.95  , 0.35  , 0.2  , -0.15  , 0.48  , 1.1  , 4.28  , -1.0  , -0.48  , -2.44  , -1.57  , -0.75  , -0.03  , 2.13  , 1.33  , 4.06 );
                        kernels[8] = compute_kernel(x,   -0.34  , 0.01  , -0.5  , -2.53  , -0.82  , -0.49  , 0.12  , -0.13  , -0.65  , 0.92  , 0.6  , 0.35  , -0.06  , 0.51  , -0.35  , -0.68  , -0.1  , -0.9  , -0.61  , -0.98  , -0.25  , -1.06  , -0.69  , -1.76  , -0.76  , -0.61  , -1.87  , 0.9  , 0.17  , -0.04  , -0.53  , -0.37  , -0.67  , 2.43  , 0.81  , 3.33  , -2.37  , -1.07  , -1.44  , -1.01  , -0.45  , -0.3  , 1.14  , 0.06  , 2.95 );
                        kernels[9] = compute_kernel(x,   -0.38  , -0.17  , -0.61  , -0.93  , -0.59  , -0.98  , -0.75  , -0.9  , -1.12  , -0.63  , -0.65  , -1.01  , -0.53  , -0.61  , -0.75  , -0.1  , -0.1  , 0.17  , 0.94  , 0.65  , 1.08  , 1.03  , 0.63  , 1.5  , 0.57  , 0.38  , -0.29  , -0.83  , -0.19  , -1.55  , 0.52  , 0.68  , 1.27  , -1.74  , -0.29  , -1.7  , 0.8  , 0.71  , 1.96  , 0.84  , 0.94  , 2.72  , 0.96  , 0.64  , 2.61 );
                        kernels[10] = compute_kernel(x,   0.12  , -0.32  , 0.15  , 0.23  , 0.06  , -0.02  , 0.12  , 0.28  , -0.06  , -0.19  , 0.21  , -0.22  , 1.16  , -0.36  , -0.18  , 0.04  , 0.04  , -0.11  , -1.39  , 0.17  , 0.36  , -1.3  , 0.2  , 0.51  , -1.16  , 0.17  , 0.58  , -1.27  , 0.23  , 0.48  , 0.0  , -0.06  , 0.0  , 0.11  , 0.05  , 0.0  , 0.01  , 0.02  , -0.04  , 0.09  , 0.04  , -0.02  , 0.13  , -0.05  , 0.14 );
                        kernels[11] = compute_kernel(x,   -0.0  , -0.0  , 0.01  , -0.0  , -0.0  , 0.01  , -0.01  , 0.0  , 0.01  , -0.0  , 0.0  , -0.0  , -0.0  , 0.0  , 0.01  , 0.0  , -0.0  , -0.0  , -0.18  , -0.46  , 0.31  , -1.0  , -0.9  , -0.48  , -1.0  , -0.9  , -0.48  , -1.01  , -0.9  , -0.49  , -0.0  , -0.0  , 0.0  , -0.0  , -0.0  , 0.01  , -0.0  , -0.01  , -0.01  , -0.0  , -0.0  , 0.0  , 0.01  , 0.01  , 0.01 );
                        kernels[12] = compute_kernel(x,   0.0  , 0.0  , -0.0  , -0.01  , -0.0  , -0.01  , 0.0  , 0.0  , 0.0  , 0.0  , 0.0  , -0.0  , 0.0  , 0.0  , 0.0  , 0.14  , -0.01  , 0.0  , 0.1  , 0.14  , -0.58  , -0.08  , -0.31  , 0.23  , -0.13  , -0.08  , 0.0  , 0.05  , -0.08  , -0.02  , 0.6  , 0.16  , 0.48  , 0.76  , 0.42  , 0.28  , 0.78  , 0.51  , -0.05  , 0.9  , 0.29  , 0.48  , 0.84  , 0.33  , 0.35 );
                        kernels[13] = compute_kernel(x,   0.6  , 0.16  , 0.48  , 0.76  , 0.42  , 0.28  , 0.78  , 0.51  , -0.05  , 0.9  , 0.29  , 0.48  , 0.84  , 0.33  , 0.35  , 0.0  , -0.01  , -0.0  , 0.09  , 0.39  , -0.08  , 0.01  , 0.66  , -0.24  , 0.04  , 0.77  , -0.38  , 0.04  , 0.76  , -0.36  , -0.01  , -0.05  , 0.13  , -0.19  , -0.16  , 0.31  , -0.21  , -0.22  , 0.41  , -0.29  , -0.16  , 0.31  , -0.35  , -0.21  , 0.35 );
                        kernels[14] = compute_kernel(x,   -0.01  , -0.0  , -0.01  , -0.72  , 0.14  , -0.25  , 0.09  , -0.63  , -0.24  , -0.01  , -0.71  , -0.26  , -0.94  , -0.04  , -0.97  , 0.36  , 0.03  , 0.3  , 1.05  , 0.24  , 0.32  , 0.56  , 0.14  , 0.38  , -0.08  , 0.14  , -0.07  , -0.13  , 0.53  , -0.4  , -0.12  , -0.25  , -0.29  , -0.05  , -0.48  , -0.55  , 0.89  , -0.28  , 0.63  , 0.41  , 0.25  , 0.34  , -0.07  , -0.45  , -0.51 );
                        kernels[15] = compute_kernel(x,   0.04  , -0.09  , -0.11  , -0.05  , 0.02  , 0.13  , -0.05  , 0.09  , 0.08  , -0.07  , -0.02  , 0.03  , 0.03  , 0.01  , 0.09  , 0.04  , -0.08  , -0.15  , -0.09  , -0.09  , -0.08  , 0.0  , -0.07  , -0.15  , -0.06  , -0.06  , -0.12  , 0.15  , -0.17  , -0.14  , -0.15  , 0.05  , 0.07  , -0.44  , 0.87  , 0.2  , 1.03  , 0.39  , -0.85  , 0.5  , 0.47  , 0.29  , -0.67  , 0.25  , -0.17 );
                        kernels[16] = compute_kernel(x,   10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0  , 10.0 );
                        decisions[0] = 0.582602400033
                        + kernels[0] * 0.479220464617
                        + kernels[1] * 0.489655455051
                        + kernels[2] * 0.436551490965
                        + kernels[3] * 0.462401162437
                        + kernels[4] * 0.417916754055
                        + kernels[5] * 0.417685427964
                        + kernels[6] * 0.417863946732
                        + kernels[7] * 0.417540712099
                        + kernels[8] * 0.421724481332
                        + kernels[9] * 0.449586141502
                        + kernels[10] * -0.892586414306
                        + kernels[11] * -0.654504090855
                        + kernels[12] * -0.482142494863
                        + kernels[13] * -0.933830207478
                        + kernels[14] * -1.050865317611
                        + kernels[15] * -0.396217511643
                        ;
                        decisions[1] = 0.81791235807
                        + kernels[0] * 0.181101914285
                        + kernels[1] * 0.181541597541
                        + kernels[2] * 0.181831097665
                        + kernels[3] * 0.181144012418
                        + kernels[4] * 0.181734228458
                        + kernels[5] * 0.181880071336
                        + kernels[6] * 0.182572842147
                        + kernels[7] * 0.181900951442
                        + kernels[8] * 0.181831637212
                        + kernels[9] * 0.181605575921
                        + kernels[16] * -1.817143928424
                        ;
                        decisions[2] = 0.465496121132
                        + kernels[10] * 0.295443819169
                        + kernels[11] * 0.218487281871
                        + kernels[12] * 0.158768324671
                        + kernels[13] * 0.311386251776
                        + kernels[14] * 0.35098326817
                        + kernels[15] * 0.130363864416
                        + kernels[16] * -1.465432810074
                        ;
                        votes[decisions[0] > 0 ? 0 : 1] += 1;
                        votes[decisions[1] > 0 ? 0 : 2] += 1;
                        votes[decisions[2] > 0 ? 1 : 2] += 1;
                        int val = votes[0];
                        int idx = 0;

                        for (int i = 1; i < 3; i++) {
                            if (votes[i] > val) {
                                val = votes[i];
                                idx = i;
                            }
                        }

                        return idx;
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