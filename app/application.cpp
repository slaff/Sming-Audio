#include <SmingCore.h>

#define DEMO_MIDI
//#define DEMO_MP3

#include <AudioOutputI2SNoDAC.h>
#include <AudioFileSourceFS.h>
#include <driver/i2s.h>

AudioOutputI2SNoDAC output;

#ifdef DEMO_MIDI

#include <AudioGeneratorMIDI.h>

AudioFileSourceFS sf2File;
AudioFileSourceFS source;
AudioGeneratorMIDI generator;

static void setup()
{
	Serial.println("Sample MIDI playback\n");

	sf2File.open("1mgm.sf2");
	source.open("furelise.mid");
	generator.SetSoundfont(&sf2File);
	generator.SetSampleRate(22050);
}

#elif defined(DEMO_MP3)

#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"

AudioFileSourceFS mp3File;
AudioFileSourceID3 source(&mp3File);
AudioGeneratorMP3 generator;

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void* cbData, const char* type, bool isUnicode, const char* string)
{
	(void)cbData;
	Serial.printf("ID3 callback for: %s = '", type);

	if(isUnicode) {
		string += 2;
	}

	while(*string) {
		char a = *(string++);
		if(isUnicode) {
			string++;
		}
		Serial.print(a);
	}
	Serial.printf("'\n");
}

static void setup()
{
	Serial.println("Sample MP3 playback");

	mp3File.open("pno-cs.mp3");
	source.RegisterMetadataCB(MDCallback, (void*)"ID3TAG");
}

#endif

static void loop()
{
	if(generator.isRunning()) {
		if(!generator.loop()) {
			generator.stop();
		}
		System.queueCallback(TaskCallback(loop));
	} else {
		Serial.println("Playback complete.");
	}
}

Timer timer;

static void onReady()
{
	spiffs_mount();

	audioLogger = &Serial;

    audioLogger->printf_P(PSTR("Logger check OK\n"));

    setup();

	i2s_set_pins(I2S_DATA_OUT, true);

	System.setCpuFrequency(eCF_160MHz);

	timer.initializeMs(1000, InterruptCallback([]() {
		Serial.print("free heap: ");
		Serial.println(system_get_free_heap_size());
	})).start();

	Serial.println("BEGIN...");
	generator.begin(&source, &output);
	loop();
}

void init()
{
	// I2S uses standard serial pins, so switch to UART1
	Serial.setPort(1);
	Serial.setTxBufferSize(1024);
	Serial.setTxWait(false);
	Serial.begin(SERIAL_BAUD_RATE);
	Serial.systemDebugOutput(true);

	Serial.println("Hello");

	System.onReady(onReady);
}
