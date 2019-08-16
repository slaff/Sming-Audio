
#pragma once

#include <stddef.h>

#define PROGMEM __attribute__((aligned(4))) __attribute__((section(".irom.text")))

/*
 * Define and use a flash string inline
 */
#define PSTR(_str)                                                                                                     \
	(__extension__({                                                                                                   \
		static const char __c[] PROGMEM = _str;                                                                        \
		&__c[0];                                                                                                       \
	}))

#ifdef ICACHE_FLASH
void *memcpy_P(void *dest, const void *src_P, size_t length);
#else
#define memcpy_P(dest, src, num) memcpy((dest), (src), (num))
#endif
