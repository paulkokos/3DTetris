//
// Created by paulkokos on 8/15/17.
//

#include "cube.h"


cube::cube() {
    active = 0;
    loaded = 0;
}

void cube::setColour(int randNum) {
    colour = randNum;
}

void cube::setPos(int indexX, int indexY, int indexZ) {
    positionX = indexX;
    positionY = indexY;
    positionZ = indexZ;
}

void cube::movePos(int x, int y, int z) {
    positionX = x;
    positionY = y;
    positionZ = z;
}

void cube::moveColour(int c) {
    colour = c;
}

int cube::getPosX() {
    return positionX;
}

int cube::getPosY() {
    return positionY;
}

int cube::getPosZ() {
    return positionZ;
}

void cube::setActive(int a) {
    active = a;
}

void cube::setLoaded(int b) {
    loaded = b;
}

int cube::getLoaded() {
    return loaded;
}

void cube::setScored(int b) {
    Scored = b;
}

int cube::getScored() {
    return Scored;
}

int cube::getActive() {
    return active;
}

int cube::getColour() {
    return colour;
}

