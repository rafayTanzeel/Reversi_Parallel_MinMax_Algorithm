/*
 * joystick_ctrl.h
 *
 *  Created on: Oct 30, 2016
 *      Author: rafaytanzeel
 */

#ifndef JOYSTICK_CTRL_H_
#define JOYSTICK_CTRL_H_

void readFile(char* filePath, char* buffer, const int size); //Reads content of file
void writeFile(char* filePath, char* input); //Writes content to file




void joystick_init();
void* joystickThread(void* arg);
int joystick_getMovement();








#endif /* JOYSTICK_CTRL_H_ */
