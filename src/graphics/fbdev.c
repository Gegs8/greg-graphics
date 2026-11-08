#include "fbdev.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

static char *devices[] = {

	"/dev/fb0",
	"/dev/fb1",
	"/dev/fb2",
	"/dev/fb3",
	"/dev/fb4",
	"/dev/fb5",
	NULL,
};

static int global_fd = -1;
static struct fb_var_screeninfo global_vinfo;
static struct fb_fix_screeninfo global_finfo;

static int check_device(char *filename);
static int check_devices();

int
init_device(struct drawplane_info *dpi)
{
	if(check_devices())
		return -1;

	dpi->width = global_vinfo.xres;
	dpi->height = global_vinfo.yres;
	dpi->pitch = global_finfo.line_length / 4; /* 4 bytes per pixel */

#define IS_FORMAT(RO,GO,BO) \
	((global_vinfo.red.length == 8 && \
	  global_vinfo.green.length == 8 && \
	  global_vinfo.blue.length == 8) && \
	 (global_vinfo.red.offset == (RO) && \
	  global_vinfo.green.offset == (GO) && \
	  global_vinfo.blue.offset == (BO)))
#define MMAP \
	do { \
		dpi->pixels = mmap(NULL, global_finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, global_fd, 0); \
		if(dpi->pixels == MAP_FAILED) { \
			close(global_fd); \
			return -1; \
		} \
	} while(0);
	if(IS_FORMAT(16, 8, 0)) {
		dpi->fmt = PIX_FMT_XRGB;
		MMAP;
		return 0;
	} else if(IS_FORMAT(24, 16, 8)) {
		dpi->fmt = PIX_FMT_RGBX;
		MMAP;
		return 0;
	} else if(IS_FORMAT(8, 16, 24)) {
		dpi->fmt = PIX_FMT_BGRX;
		MMAP;
		return 0;
	} else if(IS_FORMAT(0, 8, 16)) {
		dpi->fmt = PIX_FMT_XBGR;
		MMAP;
		return 0;
	} else {
		close(global_fd);
		return -1;
	}
#undef MMAP
#undef IS_FORMAT
}

void
destroy_device()
{
	close(global_fd);
}


int
flush_device(struct drawplane_info *dpi)
{
	(void)dpi;
	int zero = 0;
 ioctl(global_fd, FBIO_WAITFORVSYNC, &zero);


return 0;
}

static int
check_device(char *filename)
{
	global_fd = open(filename, O_RDWR | O_CLOEXEC);

	if(global_fd < 0) return -1;

	if(ioctl(global_fd, FBIOGET_VSCREENINFO, &global_vinfo) < 0)
	{
		close(global_fd);
		return -2;
	}
	if(ioctl(global_fd, FBIOGET_FSCREENINFO, &global_finfo) < 0)
	{
		close(global_fd);
		return -3;
	}
	return 0;
}

static int
check_devices()
{
	
	for(char **i = devices; *i; ++i)
	{
		if(!check_device(*i)) return 0;
	}
	return -1;
}

