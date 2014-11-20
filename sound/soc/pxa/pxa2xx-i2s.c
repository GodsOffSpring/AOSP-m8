/*
 * pxa2xx-i2s.c  --  ALSA Soc Audio Layer
 *
 * Copyright 2005 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood
 *         lrg@slimlogic.co.uk
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/soc.h>
#include <sound/pxa2xx-lib.h>

#include <mach/hardware.h>
#include <mach/dma.h>
#include <mach/audio.h>

#include "pxa2xx-i2s.h"

#define SACR0		__REG(0x40400000)  
#define SACR1		__REG(0x40400004)  
#define SASR0		__REG(0x4040000C)  
#define SAIMR		__REG(0x40400014)  
#define SAICR		__REG(0x40400018)  
#define SADIV		__REG(0x40400060)  
#define SADR		__REG(0x40400080)  

#define SACR0_RFTH(x)	((x) << 12)	
#define SACR0_TFTH(x)	((x) << 8)	
#define SACR0_STRF	(1 << 5)	
#define SACR0_EFWR	(1 << 4)	
#define SACR0_RST	(1 << 3)	
#define SACR0_BCKD	(1 << 2) 	
#define SACR0_ENB	(1 << 0)	
#define SACR1_ENLBF	(1 << 5)	
#define SACR1_DRPL	(1 << 4) 	
#define SACR1_DREC	(1 << 3)	
#define SACR1_AMSL	(1 << 0)	

#define SASR0_I2SOFF	(1 << 7)	
#define SASR0_ROR	(1 << 6)	
#define SASR0_TUR	(1 << 5)	
#define SASR0_RFS	(1 << 4)	
#define SASR0_TFS	(1 << 3)	
#define SASR0_BSY	(1 << 2)	
#define SASR0_RNE	(1 << 1)	
#define SASR0_TNF	(1 << 0) 	

#define SAICR_ROR	(1 << 6)	
#define SAICR_TUR	(1 << 5)	

#define SAIMR_ROR	(1 << 6)	
#define SAIMR_TUR	(1 << 5)	
#define SAIMR_RFS	(1 << 4)	
#define SAIMR_TFS	(1 << 3)	

struct pxa_i2s_port {
	u32 sadiv;
	u32 sacr0;
	u32 sacr1;
	u32 saimr;
	int master;
	u32 fmt;
};
static struct pxa_i2s_port pxa_i2s;
static struct clk *clk_i2s;
static int clk_ena = 0;

static struct pxa2xx_pcm_dma_params pxa2xx_i2s_pcm_stereo_out = {
	.name			= "I2S PCM Stereo out",
	.dev_addr		= __PREG(SADR),
	.drcmr			= &DRCMR(3),
	.dcmd			= DCMD_INCSRCADDR | DCMD_FLOWTRG |
				  DCMD_BURST32 | DCMD_WIDTH4,
};

static struct pxa2xx_pcm_dma_params pxa2xx_i2s_pcm_stereo_in = {
	.name			= "I2S PCM Stereo in",
	.dev_addr		= __PREG(SADR),
	.drcmr			= &DRCMR(2),
	.dcmd			= DCMD_INCTRGADDR | DCMD_FLOWSRC |
				  DCMD_BURST32 | DCMD_WIDTH4,
};

static int pxa2xx_i2s_startup(struct snd_pcm_substream *substream,
			      struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;

	if (IS_ERR(clk_i2s))
		return PTR_ERR(clk_i2s);

	if (!cpu_dai->active)
		SACR0 = 0;

	return 0;
}

static int pxa_i2s_wait(void)
{
	int i;

	
	for(i = 0; i < 16; i++)
		SADR;
	return 0;
}

static int pxa2xx_i2s_set_dai_fmt(struct snd_soc_dai *cpu_dai,
		unsigned int fmt)
{
	
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		pxa_i2s.fmt = 0;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		pxa_i2s.fmt = SACR1_AMSL;
		break;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		pxa_i2s.master = 1;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		pxa_i2s.master = 0;
		break;
	default:
		break;
	}
	return 0;
}

static int pxa2xx_i2s_set_dai_sysclk(struct snd_soc_dai *cpu_dai,
		int clk_id, unsigned int freq, int dir)
{
	if (clk_id != PXA2XX_I2S_SYSCLK)
		return -ENODEV;

	return 0;
}

static int pxa2xx_i2s_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct pxa2xx_pcm_dma_params *dma_data;

	BUG_ON(IS_ERR(clk_i2s));
	clk_enable(clk_i2s);
	clk_ena = 1;
	pxa_i2s_wait();

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_data = &pxa2xx_i2s_pcm_stereo_out;
	else
		dma_data = &pxa2xx_i2s_pcm_stereo_in;

	snd_soc_dai_set_dma_data(dai, substream, dma_data);

	
	if (!(SACR0 & SACR0_ENB)) {
		SACR0 = 0;
		if (pxa_i2s.master)
			SACR0 |= SACR0_BCKD;

		SACR0 |= SACR0_RFTH(14) | SACR0_TFTH(1);
		SACR1 |= pxa_i2s.fmt;
	}
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		SAIMR |= SAIMR_TFS;
	else
		SAIMR |= SAIMR_RFS;

	switch (params_rate(params)) {
	case 8000:
		SADIV = 0x48;
		break;
	case 11025:
		SADIV = 0x34;
		break;
	case 16000:
		SADIV = 0x24;
		break;
	case 22050:
		SADIV = 0x1a;
		break;
	case 44100:
		SADIV = 0xd;
		break;
	case 48000:
		SADIV = 0xc;
		break;
	case 96000: 
		SADIV = 0x6;
		break;
	}

	return 0;
}

static int pxa2xx_i2s_trigger(struct snd_pcm_substream *substream, int cmd,
			      struct snd_soc_dai *dai)
{
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			SACR1 &= ~SACR1_DRPL;
		else
			SACR1 &= ~SACR1_DREC;
		SACR0 |= SACR0_ENB;
		break;
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}

static void pxa2xx_i2s_shutdown(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		SACR1 |= SACR1_DRPL;
		SAIMR &= ~SAIMR_TFS;
	} else {
		SACR1 |= SACR1_DREC;
		SAIMR &= ~SAIMR_RFS;
	}

	if ((SACR1 & (SACR1_DREC | SACR1_DRPL)) == (SACR1_DREC | SACR1_DRPL)) {
		SACR0 &= ~SACR0_ENB;
		pxa_i2s_wait();
		if (clk_ena) {
			clk_disable(clk_i2s);
			clk_ena = 0;
		}
	}
}

#ifdef CONFIG_PM
static int pxa2xx_i2s_suspend(struct snd_soc_dai *dai)
{
	
	pxa_i2s.sacr0 = SACR0;
	pxa_i2s.sacr1 = SACR1;
	pxa_i2s.saimr = SAIMR;
	pxa_i2s.sadiv = SADIV;

	
	SACR0 &= ~SACR0_ENB;
	pxa_i2s_wait();
	return 0;
}

static int pxa2xx_i2s_resume(struct snd_soc_dai *dai)
{
	pxa_i2s_wait();

	SACR0 = pxa_i2s.sacr0 & ~SACR0_ENB;
	SACR1 = pxa_i2s.sacr1;
	SAIMR = pxa_i2s.saimr;
	SADIV = pxa_i2s.sadiv;

	SACR0 = pxa_i2s.sacr0;

	return 0;
}

#else
#define pxa2xx_i2s_suspend	NULL
#define pxa2xx_i2s_resume	NULL
#endif

static int pxa2xx_i2s_probe(struct snd_soc_dai *dai)
{
	clk_i2s = clk_get(dai->dev, "I2SCLK");
	if (IS_ERR(clk_i2s))
		return PTR_ERR(clk_i2s);

	SACR0 = SACR0_RST;
	SACR0 = 0;
	
	SACR1 = SACR1_DRPL | SACR1_DREC;
	
	SAIMR &= ~(SAIMR_RFS | SAIMR_TFS);

	return 0;
}

static int  pxa2xx_i2s_remove(struct snd_soc_dai *dai)
{
	clk_put(clk_i2s);
	clk_i2s = ERR_PTR(-ENOENT);
	return 0;
}

#define PXA2XX_I2S_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_44100 | \
		SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000)

static const struct snd_soc_dai_ops pxa_i2s_dai_ops = {
	.startup	= pxa2xx_i2s_startup,
	.shutdown	= pxa2xx_i2s_shutdown,
	.trigger	= pxa2xx_i2s_trigger,
	.hw_params	= pxa2xx_i2s_hw_params,
	.set_fmt	= pxa2xx_i2s_set_dai_fmt,
	.set_sysclk	= pxa2xx_i2s_set_dai_sysclk,
};

static struct snd_soc_dai_driver pxa_i2s_dai = {
	.probe = pxa2xx_i2s_probe,
	.remove = pxa2xx_i2s_remove,
	.suspend = pxa2xx_i2s_suspend,
	.resume = pxa2xx_i2s_resume,
	.playback = {
		.channels_min = 2,
		.channels_max = 2,
		.rates = PXA2XX_I2S_RATES,
		.formats = SNDRV_PCM_FMTBIT_S16_LE,},
	.capture = {
		.channels_min = 2,
		.channels_max = 2,
		.rates = PXA2XX_I2S_RATES,
		.formats = SNDRV_PCM_FMTBIT_S16_LE,},
	.ops = &pxa_i2s_dai_ops,
	.symmetric_rates = 1,
};

static int pxa2xx_i2s_drv_probe(struct platform_device *pdev)
{
	return snd_soc_register_dai(&pdev->dev, &pxa_i2s_dai);
}

static int __devexit pxa2xx_i2s_drv_remove(struct platform_device *pdev)
{
	snd_soc_unregister_dai(&pdev->dev);
	return 0;
}

static struct platform_driver pxa2xx_i2s_driver = {
	.probe = pxa2xx_i2s_drv_probe,
	.remove = __devexit_p(pxa2xx_i2s_drv_remove),

	.driver = {
		.name = "pxa2xx-i2s",
		.owner = THIS_MODULE,
	},
};

static int __init pxa2xx_i2s_init(void)
{
	clk_i2s = ERR_PTR(-ENOENT);
	return platform_driver_register(&pxa2xx_i2s_driver);
}

static void __exit pxa2xx_i2s_exit(void)
{
	platform_driver_unregister(&pxa2xx_i2s_driver);
}

module_init(pxa2xx_i2s_init);
module_exit(pxa2xx_i2s_exit);

MODULE_AUTHOR("Liam Girdwood, lrg@slimlogic.co.uk");
MODULE_DESCRIPTION("pxa2xx I2S SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-i2s");
