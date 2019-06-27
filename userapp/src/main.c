#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <memory.h>

#include "adc_capture.h"

#define MB_BYTE_NUM         (1024 * 1024)
#define ADC_SAMPLE_NUM      MB_BYTE_NUM
#define ADC_DATA_BYTES      ADC_SAMPLE_NUM * 2

int main(int argc, char *argv[])
{
    int fd0, fd1;

    int ret1 = adc_capture_init(&fd0, "/dev/adc0", ADC_SAMPLE_NUM, ADC_DATA_BYTES);
    int ret2 = adc_capture_init(&fd1, "/dev/adc1", ADC_SAMPLE_NUM, ADC_DATA_BYTES);
    if (ret1 != 0 || ret2 != 0) {
        printf("open adc failed!\n");
        exit(1);
    }

    uint8_t CH0DmaRxBuffer[ADC_DATA_BYTES];
    uint8_t CH1DmaRxBuffer[ADC_DATA_BYTES];

    const uint32_t MAX_LEN = 1024 * 1024 * 100; // 100MB
    uint8_t * const buffer = malloc(MAX_LEN);
    uint32_t bufferPos = 0;

    uint32_t count = 0;
    while(bufferPos < MAX_LEN) {
        size_t size = 0;
        if(adc_capture_start(fd0, ADC_SAMPLE_NUM, CH0DmaRxBuffer, &size)) {
            exit(1);
        }

        if(adc_capture_start(fd1, ADC_SAMPLE_NUM, CH1DmaRxBuffer, &size)) {
            exit(1);
        }

        const uint8_t *data = CH0DmaRxBuffer;
        printf("got adc data: len=%d, value=[%d, %d, %d...] count=%d\n",
                ADC_DATA_BYTES, data[0], data[1], data[2], ++count);

        memcpy(buffer + bufferPos, CH0DmaRxBuffer, size);
        if(bufferPos + ADC_SAMPLE_NUM * 2 <= MAX_LEN) {
            bufferPos += size;
        } else {
            break;
        }
    }

    printf("buffer size: %.2fM\n", (float)bufferPos / MB_BYTE_NUM);

    free(buffer);

    adc_capture_deinit(fd0);
    adc_capture_deinit(fd1);
}
