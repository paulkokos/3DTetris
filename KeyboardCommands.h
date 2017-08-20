//
// Created by paulkokos on 8/20/17.
//

#ifndef INC_3DTETRIS_KEYBOARDCOMMANDS_H
#define INC_3DTETRIS_KEYBOARDCOMMANDS_H

#include <map>

class KeyboardCommands {
private:
    int PAUSE = 1;
    int CamFlag = 0;

    /* Camera angles */
    float angleX = 0.0;
    float angleY = 0.0;
    float angleZ = 0.0;

    /* selected cube coordinates */
    int selectX = 0;
    int selectY = 0;
    int selectZ = 0;

    int listDisplayed =0;
    int alreadyMoved=0;

    int SCORE=0;

    /* later */
    int START=1;

protected:
    std::map<char, void (KeyboardCommands::*)(void)> commandsList;
public:
    KeyboardCommands() {
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

    void command27();

    void command_1();

    void command_2();

    void command_3();

    void command_4();

    void command_5();

    void command_6();

    void command_9();

    void command_0();

    void command_s();

    void command_b();

    void command_n();

    void command_g();

    void command_h();

    void command_t();

    void command_y();

    void findCommand(char function);
};


#endif //INC_3DTETRIS_KEYBOARDCOMMANDS_H
