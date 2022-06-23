AUDIO_LIB_ROOT := lib/ESP8266Audio

COMPONENT_SUBMODULES := $(AUDIO_LIB_ROOT)

COMPONENT_SRCDIRS := $(AUDIO_LIB_ROOT) \
	$(AUDIO_LIB_ROOT)/src/libhelix-mp3 \
	$(AUDIO_LIB_ROOT)/src/libmad

COMPONENT_INCDIRS := $(AUDIO_LIB_ROOT)/ \
	$(AUDIO_LIB_ROOT)/src

COMPONENT_SRCFILES := \
	$(AUDIO_LIB_ROOT)/src/AudioGeneratorAAC.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioGeneratorFLAC.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioGeneratorMIDI.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioGeneratorMOD.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioGeneratorMP3.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioGeneratorMP3a.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioGeneratorRTTTL.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioGeneratorWAV.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioLogger.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioOutputBuffer.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioOutputFilterDecimate.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioOutputMixer.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioFileSourceFS.cpp
#	$(AUDIO_LIB_ROOT)/src/AudioOutputSerialWAV.cpp \
#	$(AUDIO_LIB_ROOT)/src/AudioOutputSPIFFSWAV.cpp \
#	$(AUDIO_LIB_ROOT)/src/AudioFileSourceBuffer.cpp \
#	$(AUDIO_LIB_ROOT)/src/AudioFileSourceID3.cpp \
#	$(AUDIO_LIB_ROOT)/src/AudioFileSourcePROGMEM.cpp \
#	$(AUDIO_LIB_ROOT)/src/AudioFileStream.cpp \
	
	
ifeq ($(SMING_ARCH),Esp8266)

COMPONENT_SRCFILES += \
	$(AUDIO_LIB_ROOT)/src/AudioOutputI2S.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioOutputI2SNoDAC.cpp

else ifeq ($(SMING_ARCH),Host)

COMPONENT_SRCFILES += \
	$(AUDIO_LIB_ROOT)/src/AudioOutputSTDIO.cpp \
	$(AUDIO_LIB_ROOT)/src/AudioFileSourceSTDIO.cpp
endif

#	src/AudioFileSourceICYStream.cpp \
#	src/AudioFileSourceHTTPStream.cpp \
#	src/AudioFileSourceSD.cpp \
#	src/AudioFileSourceSPIRAMBuffer.cpp \
#