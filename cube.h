//
// Created by paulkokos on 8/15/17.
//

#ifndef INC_3DTETRIS_CUBE_H
#define INC_3DTETRIS_CUBE_H


class cube {
private:
    int colour;
    int posX, posY, posZ;
    int active;
    int loaded;
    int Scored;
    int id;
public:
    cube();

    void setColour(int randNum);

    void setPos(int indexX, int indexY, int indexZ);

    void movePos(int x, int y, int z);

    void moveColour(int c);

    int getPosX();

    int getPosY();

    int getPosZ();

    void setActive(int a);

    void setLoaded(int b);

    int getLoaded();

    void setScored(int b);

    int getScored();

    int getActive();

    int getColour();

};


#endif //INC_3DTETRIS_CUBE_H
