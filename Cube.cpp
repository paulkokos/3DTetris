//
// Created by paulkokos on 8/15/17.
//

#include "Cube.h"


Cube::Cube() {
    active = 0;
    loaded = 0;
}

void Cube::setColour(int randNum) {
    colour = randNum;
}

void Cube::setPos(int indexX, int indexY, int indexZ) {
    positionX = indexX;
    positionY = indexY;
    positionZ = indexZ;
}

void Cube::movePos(int x, int y, int z) {
    positionX = x;
    positionY = y;
    positionZ = z;
}

void Cube::moveColour(int c) {
    colour = c;
}

int Cube::getPosX() {
    return positionX;
}

int Cube::getPosY() {
    return positionY;
}

int Cube::getPosZ() {
    return positionZ;
}

void Cube::setActive(int a) {
    active = a;
}

void Cube::setLoaded(int b) {
    loaded = b;
}

int Cube::getLoaded() {
    return loaded;
}

void Cube::setScored(int b) {
    Scored = b;
}

int Cube::getScored() {
    return Scored;
}

int Cube::getActive() {
    return active;
}

int Cube::getColour() {
    return colour;
}