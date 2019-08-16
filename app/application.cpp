#include <SmingCore.h>

#define DEMO_MIDI
//#define DEMO_MP3


template <typename File>
bool openFile(File& f, const char* filename)
{
	if(f.open(filename)) {
		debug_i("Opened '%s'", filename);
		return true;
	} else {
		debug_e("Failed to open '%s'", filename);
		return false;
	}
}


#ifdef ARCH_HOST

#include <AudioOutputSTDIO.h>

AudioOutputSTDIO output;

#else
#include <AudioOutputI2SNoDAC.h>
#include <driver/i2s.h>

AudioOutputI2SNoDAC output;

#endif

#include <AudioFileSourceFS.h>

#ifdef DEMO_MIDI

#include <AudioGeneratorMIDI.h>

AudioFileSourceFS sf2File;
AudioFileSourceFS source;
AudioGeneratorMIDI generator;

static void setup()
{
	Serial.println("Sample MIDI playback\n");

	openFile(sf2File, "1mgm.sf2");
	openFile(source, "furelise.mid"));
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

	openFile(mp3File, "pno-cs.mp3");
	source.RegisterMetadataCB(MDCallback, (void*)"ID3TAG");
#ifdef ARCH_HOST
	output.SetFilename("test-out.wav");
#endif
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

#ifndef ARCH_HOST
	i2s_set_pins(I2S_PIN_DATA_OUT, true);
#endif

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
#ifdef ARCH_ESP8266
	// I2S uses standard serial pins, so switch to UART1
	Serial.setPort(1);
#endif
	Serial.setTxBufferSize(1024);
	Serial.setTxWait(false);
	Serial.begin(SERIAL_BAUD_RATE);
	Serial.systemDebugOutput(true);

	Serial.println("Hello");

	System.onReady(onReady);
}
