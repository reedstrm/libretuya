/* Copyright (c) Kuba Szczodrzyński 2022-04-29. */

#include "LibreTuyaAPI.h"

String ipToString(const IPAddress &ip) {
	char szRet[16];
	sprintf(szRet, "%hhu.%hhu.%hhu.%hhu", ip[0], ip[1], ip[2], ip[3]);
	return String(szRet);
}

/**
 * @brief Generate random bytes using rand().
 *
 * @param buf destination pointer
 * @param len how many bytes to generate
 */
extern "C" {
void lt_rand_bytes(uint8_t *buf, size_t len) {
	int *data = (int *)buf;
	size_t i;
	for (i = 0; len >= sizeof(int); len -= sizeof(int)) {
		data[i++] = rand();
	}
	if (len) {
		int rem				= rand();
		unsigned char *pRem = (unsigned char *)&rem;
		memcpy(buf + i * sizeof(int), pRem, len);
	}
}

#undef putchar

/**
 * @brief Print data pointed to by buf in hexdump-like format (hex+ASCII).
 *
 * @param buf source pointer
 * @param len how many bytes to print
 * @param offset increment printed offset by this value
 * @param width how many bytes on a line
 */
void hexdump(const uint8_t *buf, size_t len, uint32_t offset, uint8_t width) {
	uint16_t pos = 0;
	while (pos < len) {
		// print hex offset
		printf("%06x ", offset + pos);
		// calculate current line width
		uint8_t lineWidth = min(width, len - pos);
		// print hexadecimal representation
		for (uint8_t i = 0; i < lineWidth; i++) {
			if (i % 8 == 0) {
				printf(" ");
			}
			printf("%02x ", buf[pos + i]);
		}
		// print ascii representation
		printf(" |");
		for (uint8_t i = 0; i < lineWidth; i++) {
			char c = buf[pos + i];
			putchar((c >= 0x20 && c <= 0x7f) ? c : '.');
		}
		puts("|\r");
		pos += lineWidth;
	}
}
}
