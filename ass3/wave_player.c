/*
 *  Small program to read a 16-bit, signed, 44.1kHz wave file and play it.
 *  Written by Brian Fraser, heavily based on code found at:
 *  http://www.alsa-project.org/alsa-doc/alsa-lib/_2test_2pcm_min_8c-example.html
 */

#include <alsa/asoundlib.h>
#include <stdbool.h>
#include "audioMixer_template.h"
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

char* beatbox_fileName[]={"100051__menegass__gui-drum-bd-hard.wav","100052__menegass__gui-drum-bd-soft.wav","100053__menegass__gui-drum-cc.wav","100054__menegass__gui-drum-ch.wav","100055__menegass__gui-drum-co.wav","100056__menegass__gui-drum-cyn-hard.wav","100057__menegass__gui-drum-cyn-soft.wav","100058__menegass__gui-drum-snare-hard.wav","100059__menegass__gui-drum-snare-soft.wav","100060__menegass__gui-drum-splash-hard.wav","100061__menegass__gui-drum-splash-soft.wav","100062__menegass__gui-drum-tom-hi-hard.wav","100063__menegass__gui-drum-tom-hi-soft.wav","100064__menegass__gui-drum-tom-lo-hard.wav","100065__menegass__gui-drum-tom-lo-soft.wav","100066__menegass__gui-drum-tom-mid-hard.wav","100067__menegass__gui-drum-tom-mid-soft.wav"};



int main(void)
{

	// Configure Output Device
	AudioMixer_init();

	// Load wave file we want to play:
	wavedata_t hithatFile;
	wavedata_t snareFile;
	wavedata_t basedrumFile;

	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_HH, &hithatFile);
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_SN, &snareFile);
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_BD, &basedrumFile);

	// Play Audio

	//Hi-hat, Base
	AudioMixer_queueSound(&hithatFile);
	AudioMixer_queueSound(&basedrumFile);

	//Hi-hat
	AudioMixer_queueSound(&hithatFile);

	//Hi-hat, Snare
	AudioMixer_queueSound(&hithatFile);
	AudioMixer_queueSound(&snareFile);

	//Hi-hat
	AudioMixer_queueSound(&hithatFile);




//	sleep(10);
	//Freeing sound file data
	AudioMixer_cleanup();

	AudioMixer_freeWaveFileData(&hithatFile);
	AudioMixer_freeWaveFileData(&snareFile);
	AudioMixer_freeWaveFileData(&basedrumFile);

	printf("Done!\n");
	return 0;
}



