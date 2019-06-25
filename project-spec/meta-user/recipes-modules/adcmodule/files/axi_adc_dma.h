#ifndef AXI_ADC_DMA_H
#define AXI_ADC_DMA_H

#define MODULE_NAME                     "axi_adc_dma"
#define AXI_ADC_MINOR_START             0
#define AXI_ADC_MINOR_COUNT             16
#define AXI_ADC_CALLBACK_TIMEOUTMSEC    10000
#define SUCCESS                         0
#define FAILURE                         -1
#define MAX_BUF_COUNT                   8
/* IOCTL defines */
#define AXI_ADC_IOCTL_BASE              'W'
#define AXI_ADC_SET_SAMPLE_NUM          _IO(AXI_ADC_IOCTL_BASE, 0)
#define AXI_ADC_SET_DMA_LEN_BYTES       _IO(AXI_ADC_IOCTL_BASE, 1)
#define AXI_ADC_DMA_INIT                _IO(AXI_ADC_IOCTL_BASE, 2)
#define AXI_ADC_DMA_START               _IO(AXI_ADC_IOCTL_BASE, 3)
#define AXI_ADC_DMA_DEINIT              _IO(AXI_ADC_IOCTL_BASE, 4)

struct axi_adc_dev
{
    struct mutex mutex;
    struct platform_device *pdev;
    /* ADC Hardware device constants */
    void *adc_virtaddr;
    /* DMA stuff */
    struct dma_chan *rx_chan;
    dma_cookie_t rx_cookie;
    struct completion rx_cmp;
    unsigned long rx_tmo;
    int bd_cnt;
    struct scatterlist *rx_sg;
    /*DMA address of buffer */
    dma_addr_t *dma_dsts;
    u8 **dsts;
    int adc_sample_num;
    int dma_len_bytes;
};

#endif
