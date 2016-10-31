/*
 *  Small program to read a 16-bit, signed, 44.1kHz wave file and play it.
 *  Written by Brian Fraser, heavily based on code found at:
 *  http://www.alsa-project.org/alsa-doc/alsa-lib/_2test_2pcm_min_8c-example.html
 */

#include <alsa/asoundlib.h>
#include <stdbool.h>
#include "audioMixer_template.h"
#include "joystick_ctrl.h"
#include  "zencape_inputCtrl.h"






int main(void)
{
	// Configure Output Device
	zencape_init();



	sleep(100);
	//Freeing sound file data


	printf("Done!\n");
	return 0;
}






