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


// File used for play-back:
// If cross-compiling, must have this file available, via this relative path,
// on the target when the application is run. This example's Makefile copies the wave-files/
// folder along with the executable to ensure both are present.
#define SOURCE_FILE_BD "beatbox-wav-files/100051__menegass__gui-drum-bd-hard.wav" //Base Drum
#define SOURCE_FILE_SN "beatbox-wav-files/100059__menegass__gui-drum-snare-soft.wav" //Snare
#define SOURCE_FILE_HH "beatbox-wav-files/100053__menegass__gui-drum-cc.wav" //HitHat
//#define SOURCE_FILE "wave-files/100053__menegass__gui-drum-cc.wav"

#define SAMPLE_RATE   44100
#define NUM_CHANNELS  1
#define SAMPLE_SIZE   (sizeof(short)) 	// bytes per sample

char* beatbox_fileName[]={"beatbox-wav-files/100051__menegass__gui-drum-bd-hard.wav","beatbox-wav-files/100052__menegass__gui-drum-bd-soft.wav","beatbox-wav-files/100053__menegass__gui-drum-cc.wav","beatbox-wav-files/100054__menegass__gui-drum-ch.wav","beatbox-wav-files/100055__menegass__gui-drum-co.wav","beatbox-wav-files/100056__menegass__gui-drum-cyn-hard.wav","beatbox-wav-files/100057__menegass__gui-drum-cyn-soft.wav","beatbox-wav-files/100058__menegass__gui-drum-snare-hard.wav","beatbox-wav-files/100059__menegass__gui-drum-snare-soft.wav","beatbox-wav-files/100060__menegass__gui-drum-splash-hard.wav","beatbox-wav-files/100061__menegass__gui-drum-splash-soft.wav","beatbox-wav-files/100062__menegass__gui-drum-tom-hi-hard.wav","beatbox-wav-files/100063__menegass__gui-drum-tom-hi-soft.wav","beatbox-wav-files/100064__menegass__gui-drum-tom-lo-hard.wav","beatbox-wav-files/100065__menegass__gui-drum-tom-lo-soft.wav","beatbox-wav-files/100066__menegass__gui-drum-tom-mid-hard.wav","beatbox-wav-files/100067__menegass__gui-drum-tom-mid-soft.wav"};

void standard_beats();
void custom_beats();
//BPM 40 to 300
int BPM = 120;


int main(void)
{

//	zencape_init();
//	joystick_init();
//	// Configure Output Device
//	AudioMixer_init();
//
////	custom_beats();
//	standard_beats();





	sleep(20);
	//Freeing sound file data


	printf("Done!\n");
	return 0;
}


void standard_beats(){

		// Load wave file we want to play:
		wavedata_t hithatFile;
		wavedata_t snareFile;
		wavedata_t basedrumFile;

		AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_HH, &hithatFile);
		AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_SN, &snareFile);
		AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_BD, &basedrumFile);

		// Play Audio


		long delay=((60.0/BPM)/2.0)*1000000000;
//		printf("%ld\n",delay);

		while(true){
			//Hi-hat, Base
			AudioMixer_queueSound(&hithatFile);
			AudioMixer_queueSound(&basedrumFile);
			nanosleep((const struct timespec[]){{0, delay}}, NULL);

			//Hi-hat
			AudioMixer_queueSound(&hithatFile);
			nanosleep((const struct timespec[]){{0, delay}}, NULL);

			//Hi-hat, Snare
			AudioMixer_queueSound(&hithatFile);
			AudioMixer_queueSound(&snareFile);
			nanosleep((const struct timespec[]){{0, delay}}, NULL);

			//Hi-hat
			AudioMixer_queueSound(&hithatFile);

		}

		AudioMixer_cleanup();

		AudioMixer_freeWaveFileData(&hithatFile);
		AudioMixer_freeWaveFileData(&snareFile);
		AudioMixer_freeWaveFileData(&basedrumFile);

}


void custom_beats(){

		// Load wave file we want to play:
		wavedata_t hithatFile;
		wavedata_t snareFile;
		wavedata_t basedrumFile;

		AudioMixer_readWaveFileIntoMemory(beatbox_fileName[8], &hithatFile);
		AudioMixer_readWaveFileIntoMemory(beatbox_fileName[13], &snareFile);
		AudioMixer_readWaveFileIntoMemory(beatbox_fileName[7], &basedrumFile);

		// Play Audio

		//BPM 40 to 300
		int BPM = 40;
		long delay=((60.0/BPM)/2.0)*1000000000;
//		printf("%ld\n",delay);

		while(true){
			//Hi-hat, Base
			AudioMixer_queueSound(&hithatFile);
			AudioMixer_queueSound(&basedrumFile);
			nanosleep((const struct timespec[]){{0, delay}}, NULL);

			//Hi-hat
			AudioMixer_queueSound(&hithatFile);
			nanosleep((const struct timespec[]){{0, delay}}, NULL);

			//Hi-hat, Snare
			AudioMixer_queueSound(&hithatFile);
			AudioMixer_queueSound(&snareFile);
			nanosleep((const struct timespec[]){{0, delay}}, NULL);

			//Hi-hat
			AudioMixer_queueSound(&hithatFile);

		}

		AudioMixer_cleanup();

		AudioMixer_freeWaveFileData(&hithatFile);
		AudioMixer_freeWaveFileData(&snareFile);
		AudioMixer_freeWaveFileData(&basedrumFile);

}



