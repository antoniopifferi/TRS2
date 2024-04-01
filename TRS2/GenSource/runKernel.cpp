#include <iostream>
#include "GenSource/runKernel.h"
#include "ParmS.h"

void runKernel() {
    for (P.Loop[0].Actual = P.Loop[0].First; P.Loop[0].Actual <= P.Loop[0].Last; P.Loop[0].Actual += P.Loop[0].Delta) {
        for (P.Loop[1].Actual = P.Loop[1].First; P.Loop[1].Actual <= P.Loop[1].Last; P.Loop[1].Actual += P.Loop[1].Delta) {
            for (P.Loop[2].Actual = P.Loop[2].First; P.Loop[2].Actual <= P.Loop[2].Last; P.Loop[2].Actual += P.Loop[2].Delta) {
                for (P.Loop[3].Actual = P.Loop[3].First; P.Loop[3].Actual <= P.Loop[3].Last; P.Loop[3].Actual += P.Loop[3].Delta) {
                    for (P.Loop[4].Actual = P.Loop[4].First; P.Loop[4].Actual <= P.Loop[4].Last; P.Loop[4].Actual += P.Loop[4].Delta) {

                        std::cout << "index= "<<P.Loop[0].Actual<<", "<<P.Loop[1].Actual<<", "<<P.Loop[2].Actual<<", "<<P.Loop[3].Actual<<", "<<P.Loop[4].Actual<<", "<<std::endl;
                    }
                }
            }
        }
    }
}
