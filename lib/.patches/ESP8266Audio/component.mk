COMPONENT_SRCDIRS := \
	src/libhelix-mp3 \
	src/libmad

COMPONENT_INCDIRS := \
	src

COMPONENT_SRCFILES := \
	src/AudioGeneratorAAC.cpp \
	src/AudioGeneratorFLAC.cpp \
	src/AudioGeneratorMIDI.cpp \
	src/AudioGeneratorMOD.cpp \
	src/AudioGeneratorMP3.cpp \
	src/AudioGeneratorMP3a.cpp \
	src/AudioGeneratorRTTTL.cpp \
	src/AudioGeneratorWAV.cpp \
	src/AudioLogger.cpp \
	src/AudioOutputBuffer.cpp \
	src/AudioOutputFilterDecimate.cpp \
	src/AudioOutputMixer.cpp \
	src/AudioOutputSerialWAV.cpp \
	src/AudioOutputWAV.cpp \
	src/AudioOutputSPIFFSWAV.cpp \
	src/AudioFileSourceBuffer.cpp \
	src/AudioFileSourceID3.cpp \
	src/AudioFileSourcePROGMEM.cpp \
	src/AudioFileStream.cpp \
	src/AudioFileSourceFS.cpp
	
ifeq ($(SMING_ARCH),Esp8266)

COMPONENT_SRCFILES += \
	src/AudioOutputI2S.cpp \
	src/AudioOutputI2SNoDAC.cpp

else ifeq ($(SMING_ARCH),Host)

COMPONENT_SRCFILES += \
	src/AudioOutputSTDIO.cpp \
	src/AudioFileSourceSTDIO.cpp
endif

#	src/AudioFileSourceICYStream.cpp \
#	src/AudioFileSourceHTTPStream.cpp \
#	src/AudioFileSourceSD.cpp \
#	src/AudioFileSourceSPIRAMBuffer.cpp \
#	