//
// Created by paulkokos on 8/20/17.
//

#include "KeyboardCommands.h"
#include "Glut.h"

using namespace std;

KeyboardCommands::KeyboardCommands() {
    commandsList['1'] = &KeyboardCommands::command_1;
    commandsList['2'] = &KeyboardCommands::command_2;
    commandsList['3'] = &KeyboardCommands::command_3;
    commandsList['4'] = &KeyboardCommands::command_4;
    commandsList['5'] = &KeyboardCommands::command_5;
    commandsList['6'] = &KeyboardCommands::command_6;
    commandsList['9'] = &KeyboardCommands::command_9;
    commandsList['0'] = &KeyboardCommands::command_0;
    commandsList['s'] = &KeyboardCommands::command_s;
    commandsList['b'] = &KeyboardCommands::command_b;
    commandsList['n'] = &KeyboardCommands::command_n;
    commandsList['g'] = &KeyboardCommands::command_g;
    commandsList['h'] = &KeyboardCommands::command_h;
    commandsList['t'] = &KeyboardCommands::command_t;
    commandsList['y'] = &KeyboardCommands::command_y;
}

void void KeyboardCommands::command27() {
    std::exit(EXIT_SUCCESS);
}

void KeyboardCommands::command_1() {
    CamFlag = 1;
    angleX = angleX + 10;
    glRotatef(angleX, 1.f, 0.f, 0.f);
    angleX = 0.0;

}

void KeyboardCommands::command_2() {
    CamFlag = 1;
    angleX = angleX - 10;
    glRotatef(angleX, 1.f, 0.f, 0.f);
    angleX = 0.0;
}

void KeyboardCommands::command_3() {
    CamFlag = 1;
    angleY = angleY + 10;
    glRotatef(angleY, 0.f, 1.f, 0.f);
    angleY = 0.0;
}

void KeyboardCommands::command_4() {
    CamFlag = 1;
    angleY = angleY - 10;
    glRotatef(angleY, 0.f, 1.f, 0.f);
    angleY = 0.0;
}

void KeyboardCommands::command_5() {
    CamFlag = 1;
    angleZ = angleZ + 10;;
    glRotatef(angleZ, 0.f, 0.f, 1.f);
    angleZ = 0.0;
}

void KeyboardCommands::command_6() {
    CamFlag = 1;
    angleZ = angleZ - 10;
    glRotatef(angleZ, 0.f, 0.f, 1.f);
    angleZ = 0.0;
}

void KeyboardCommands::command_9() {
    glScalef(1.2, 1.2, 1.2);
}

void KeyboardCommands::command_0() {
    glScalef(0.8, 0.8, 0.8);
}


void KeyboardCommands::command_s() {
    if (PAUSE == 0) {
        PAUSE = 1;
        alreadyMoved = 0;
        listDisplayed = 0;
        SCORE = 0;
        computeScore();
        ComputeScoreKoiloX();
        ComputeScoreKoiloY();
        ComputeScoreKoiloZ();
        cout << "SCORE_final : " << SCORE << endl;
        selectX = 0;
        selectY = 0;
        selectZ = 0;

    } else {
        PAUSE = 0;
        selectX = -1;
        selectY = -1;
        selectZ = -1;

    }
    if (START == 1) {
        moveDown(10);
        START = 0;
    }
}

void KeyboardCommands::command_b() {
    if ((PAUSE == 1) && (selectX < 14)) {
        selectX++;
    }
}

void KeyboardCommands::command_n() {
    if ((PAUSE == 1) && (selectX > 0)) {
        selectX--;
    }
}

void KeyboardCommands::command_g() {
    if ((PAUSE == 1) && (selectY < 14)) {
        selectY++;
    }
}

void KeyboardCommands::command_h() {
    if ((PAUSE == 1) && (selectY > 0)) {
        selectY--;
    }
}

void KeyboardCommands::command_t() {
    if ((PAUSE == 1) && (selectZ < 14)) {
        selectZ++;
    }


}

void KeyboardCommands::command_y() {
    if ((PAUSE == 1) && (selectZ > 0)) {
        selectZ--;
    }

}
void KeyboardCommands::findCommand(char function) {
    map<char, void (KeyboardCommands::*)(void)>::iterator x = commandsList.find(function);

    if (x!= commandsList.end()) {
        //cout << x->first;
        (this->*((*x).second))();
    }
}