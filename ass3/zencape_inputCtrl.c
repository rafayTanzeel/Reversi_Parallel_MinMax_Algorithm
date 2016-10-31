#include "zencape_inputCtrl.h"
#include <stdbool.h>
#include <pthread.h>
#include "audioMixer_template.h"
#include "joystick_ctrl.h"
#include "accelerometerCtrl.h"




#define MAX_TEMPO 300
#define MIN_TEMPO 40

#define MAX_VOLUME 100
#define MIN_VOLUME 0

#define TOTAL_MENUS 3;

static pthread_t zencapeThreadId;

static int menu=0;
static int volume=80;
static int tempo=120;
static int movement=0;




void zencape_init(void){
	menu=0;
	volume=AudioMixer_getVolume();
	tempo=AudioMixer_getBPM();
	movement=joystick_getMovement();

	joystick_init();
	AudioMixer_init();
	accelerometer_init();
	// Launch playback thread:
	pthread_create(&zencapeThreadId, NULL, zencapeThread, NULL);

}

void* zencapeThread(void* arg){
	while(true){
			volume=AudioMixer_getVolume();
			tempo=AudioMixer_getBPM();
			movement=joystick_getMovement();

			(menu!=2)?beat_sequencer():NULL;
			update_postionVal();

			switch (movement) {
			case 00001: //Up Movement
				AudioMixer_setVolume((volume+5>MAX_VOLUME)?MAX_VOLUME:volume+5);
				break;
			case 00010: //Dn Movement
				AudioMixer_setVolume((volume-5<MIN_VOLUME)?MIN_VOLUME:volume-5);
				break;
			case 00100: //Lft Movement
				AudioMixer_setBPM((tempo+5>MAX_TEMPO)?MAX_TEMPO:tempo+5);
				break;
			case 01000: //Rt Movement
				AudioMixer_setBPM((tempo-5<MIN_TEMPO)?MIN_TEMPO:tempo-5);
				break;
			case 10000: //Pb Movement
				++menu;
				menu%=TOTAL_MENUS;

				if (menu == 0) {
					standard_beats();
				} else if (menu == 1) {
					custom_beats();
				} else {
					AudioMixer_freeFileDatas();
				}

				break;
			default:    //No Movement
				break;
			}
		}

}
