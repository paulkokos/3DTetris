//
// Created by paulkokos on 8/20/17.
//

#include "Generator.h"
#include "Glut.h"

int Generator::generateNum() {
    srand(static_cast<unsigned int>(time(NULL)));
    int num;
    num = 1 + (rand() % 3);
    return num;
}

int Generator::randPosX() {
    int num;
    srand(static_cast<unsigned int>(time(NULL) + 10));
    num = 0 + (rand() % 15);
    return num;
}

int Generator::randPosY() {
    int num;
    srand(static_cast<unsigned int>(time(NULL) + 20));
    num = 0 + (rand() % 15);
    return num;
}
