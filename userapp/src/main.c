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

#define ADC_SAMPLE_NUM      1024
#define ADC_DATA_BYTES      ADC_SAMPLE_NUM

int main(int argc, char *argv[])
{
    int fd0, fd1;

    int ret = adc_capture_init(&fd0, "/dev/adc0", ADC_SAMPLE_NUM, ADC_DATA_BYTES);
    if (ret != 0) {
        printf("open adc failed!\n");
        return ret;
    }

    uint8_t CH0DmaRxBuffer[ADC_DATA_BYTES];

    size_t size = 0;
    if(adc_capture_start(fd0, ADC_SAMPLE_NUM, CH0DmaRxBuffer, &size)) {
        exit(1);
    }

    const uint8_t *data = CH0DmaRxBuffer;
    printf("Got adc: len:%d, data:\n", size);
    for (int i=0; i<size / 2; i++) {
        printf("%2x ", data[i]);
        if ((i+1)%10 == 0) printf("\n");
    }
    printf("\n");
}
