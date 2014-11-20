/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> for ST-Ericsson
 * License terms: GNU General Public License (GPL) version 2
 *
 * DB5500-SoC-specific configuration for DMA40
 */

#ifndef STE_DMA40_DB5500_H
#define STE_DMA40_DB5500_H

#define DB5500_DMA_NR_DEV 64

enum dma_src_dev_type {
	DB5500_DMA_DEV0_SPI0_RX = 0,
	DB5500_DMA_DEV1_SPI1_RX = 1,
	DB5500_DMA_DEV2_SPI2_RX = 2,
	DB5500_DMA_DEV3_SPI3_RX = 3,
	DB5500_DMA_DEV4_USB_OTG_IEP_1_9 = 4,
	DB5500_DMA_DEV5_USB_OTG_IEP_2_10 = 5,
	DB5500_DMA_DEV6_USB_OTG_IEP_3_11 = 6,
	DB5500_DMA_DEV7_IRDA_RFS = 7,
	DB5500_DMA_DEV8_IRDA_FIFO_RX = 8,
	DB5500_DMA_DEV9_MSP0_RX = 9,
	DB5500_DMA_DEV10_MSP1_RX = 10,
	DB5500_DMA_DEV11_MSP2_RX = 11,
	DB5500_DMA_DEV12_UART0_RX = 12,
	DB5500_DMA_DEV13_UART1_RX = 13,
	DB5500_DMA_DEV14_UART2_RX = 14,
	DB5500_DMA_DEV15_UART3_RX = 15,
	DB5500_DMA_DEV16_USB_OTG_IEP_8 = 16,
	DB5500_DMA_DEV17_USB_OTG_IEP_1_9 = 17,
	DB5500_DMA_DEV18_USB_OTG_IEP_2_10 = 18,
	DB5500_DMA_DEV19_USB_OTG_IEP_3_11 = 19,
	DB5500_DMA_DEV20_USB_OTG_IEP_4_12 = 20,
	DB5500_DMA_DEV21_USB_OTG_IEP_5_13 = 21,
	DB5500_DMA_DEV22_USB_OTG_IEP_6_14 = 22,
	DB5500_DMA_DEV23_USB_OTG_IEP_7_15 = 23,
	DB5500_DMA_DEV24_SDMMC0_RX = 24,
	DB5500_DMA_DEV25_SDMMC1_RX = 25,
	DB5500_DMA_DEV26_SDMMC2_RX = 26,
	DB5500_DMA_DEV27_SDMMC3_RX = 27,
	DB5500_DMA_DEV28_SDMMC4_RX = 28,
	
	DB5500_DMA_DEV33_SDMMC0_RX = 33,
	DB5500_DMA_DEV34_SDMMC1_RX = 34,
	DB5500_DMA_DEV35_SDMMC2_RX = 35,
	DB5500_DMA_DEV36_SDMMC3_RX = 36,
	DB5500_DMA_DEV37_SDMMC4_RX = 37,
	DB5500_DMA_DEV38_USB_OTG_IEP_8 = 38,
	DB5500_DMA_DEV39_USB_OTG_IEP_1_9 = 39,
	DB5500_DMA_DEV40_USB_OTG_IEP_2_10 = 40,
	DB5500_DMA_DEV41_USB_OTG_IEP_3_11 = 41,
	DB5500_DMA_DEV42_USB_OTG_IEP_4_12 = 42,
	DB5500_DMA_DEV43_USB_OTG_IEP_5_13 = 43,
	DB5500_DMA_DEV44_USB_OTG_IEP_6_14 = 44,
	DB5500_DMA_DEV45_USB_OTG_IEP_7_15 = 45,
	
	DB5500_DMA_DEV47_MCDE_RX = 47,
	DB5500_DMA_DEV48_CRYPTO1_RX = 48,
	
	DB5500_DMA_DEV49_I2C1_RX = 51,
	DB5500_DMA_DEV50_I2C3_RX = 52,
	DB5500_DMA_DEV51_I2C2_RX = 53,
	
	DB5500_DMA_DEV61_CRYPTO0_RX = 61,
	
};

enum dma_dest_dev_type {
	DB5500_DMA_DEV0_SPI0_TX = 0,
	DB5500_DMA_DEV1_SPI1_TX = 1,
	DB5500_DMA_DEV2_SPI2_TX = 2,
	DB5500_DMA_DEV3_SPI3_TX = 3,
	DB5500_DMA_DEV4_USB_OTG_OEP_1_9 = 4,
	DB5500_DMA_DEV5_USB_OTG_OEP_2_10 = 5,
	DB5500_DMA_DEV6_USB_OTG_OEP_3_11 = 6,
	DB5500_DMA_DEV7_IRRC_TX = 7,
	DB5500_DMA_DEV8_IRDA_FIFO_TX = 8,
	DB5500_DMA_DEV9_MSP0_TX = 9,
	DB5500_DMA_DEV10_MSP1_TX = 10,
	DB5500_DMA_DEV11_MSP2_TX = 11,
	DB5500_DMA_DEV12_UART0_TX = 12,
	DB5500_DMA_DEV13_UART1_TX = 13,
	DB5500_DMA_DEV14_UART2_TX = 14,
	DB5500_DMA_DEV15_UART3_TX = 15,
	DB5500_DMA_DEV16_USB_OTG_OEP_8 = 16,
	DB5500_DMA_DEV17_USB_OTG_OEP_1_9 = 17,
	DB5500_DMA_DEV18_USB_OTG_OEP_2_10 = 18,
	DB5500_DMA_DEV19_USB_OTG_OEP_3_11 = 19,
	DB5500_DMA_DEV20_USB_OTG_OEP_4_12 = 20,
	DB5500_DMA_DEV21_USB_OTG_OEP_5_13 = 21,
	DB5500_DMA_DEV22_USB_OTG_OEP_6_14 = 22,
	DB5500_DMA_DEV23_USB_OTG_OEP_7_15 = 23,
	DB5500_DMA_DEV24_SDMMC0_TX = 24,
	DB5500_DMA_DEV25_SDMMC1_TX = 25,
	DB5500_DMA_DEV26_SDMMC2_TX = 26,
	DB5500_DMA_DEV27_SDMMC3_TX = 27,
	DB5500_DMA_DEV28_SDMMC4_TX = 28,
	
	DB5500_DMA_DEV32_FSMC_TX = 32,
	DB5500_DMA_DEV33_SDMMC0_TX = 33,
	DB5500_DMA_DEV34_SDMMC1_TX = 34,
	DB5500_DMA_DEV35_SDMMC2_TX = 35,
	DB5500_DMA_DEV36_SDMMC3_TX = 36,
	DB5500_DMA_DEV37_SDMMC4_TX = 37,
	DB5500_DMA_DEV38_USB_OTG_OEP_8 = 38,
	DB5500_DMA_DEV39_USB_OTG_OEP_1_9 = 39,
	DB5500_DMA_DEV40_USB_OTG_OEP_2_10 = 40,
	DB5500_DMA_DEV41_USB_OTG_OEP_3_11 = 41,
	DB5500_DMA_DEV42_USB_OTG_OEP_4_12 = 42,
	DB5500_DMA_DEV43_USB_OTG_OEP_5_13 = 43,
	DB5500_DMA_DEV44_USB_OTG_OEP_6_14 = 44,
	DB5500_DMA_DEV45_USB_OTG_OEP_7_15 = 45,
	
	DB5500_DMA_DEV47_STM_TX = 47,
	DB5500_DMA_DEV48_CRYPTO1_TX = 48,
	DB5500_DMA_DEV49_CRYPTO1_TX_HASH1_TX = 49,
	DB5500_DMA_DEV50_HASH1_TX = 50,
	DB5500_DMA_DEV51_I2C1_TX = 51,
	DB5500_DMA_DEV52_I2C3_TX = 52,
	DB5500_DMA_DEV53_I2C2_TX = 53,
	
	DB5500_DMA_MEMCPY_TX_1 = 56,
	DB5500_DMA_MEMCPY_TX_2 = 57,
	DB5500_DMA_MEMCPY_TX_3 = 58,
	DB5500_DMA_MEMCPY_TX_4 = 59,
	DB5500_DMA_MEMCPY_TX_5 = 60,
	DB5500_DMA_DEV61_CRYPTO0_TX = 61,
	DB5500_DMA_DEV62_CRYPTO0_TX_HASH0_TX = 62,
	DB5500_DMA_DEV63_HASH0_TX = 63,
};

#endif
