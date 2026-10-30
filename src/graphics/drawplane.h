#ifndef DRAWPLANE_H
#define DRAWPLANE_H

#include <stddef.h>
#include <stdint.h>

enum pix_fmt {
	/* A = 0xff -> opaque */
	/* A = 0x00 -> transparent */
	PIX_FMT_XRGB,
	PIX_FMT_ARGB,
	PIX_FMT_RGBX,
	PIX_FMT_RGBA,
	PIX_FMT_XBGR,
	PIX_FMT_ABGR,
	PIX_FMT_BGRX,
	PIX_FMT_BGRA,
};

struct drawplane_info {
	unsigned int width;
	unsigned int height;
	size_t pitch;
	uint32_t *restrict pixels;
	enum pix_fmt fmt;
};

static inline void
put_pix(struct drawplane_info *dpi, uint32_t canonic_xrgb, unsigned int x, unsigned int y) {
	switch(dpi->fmt) {
	case PIX_FMT_XRGB:
		dpi->pixels[y * dpi->pitch + x] = canonic_xrgb;
		break;
	case PIX_FMT_ARGB:
		dpi->pixels[y * dpi->pitch + x] = (canonic_xrgb & 0x00ffffff) | 0xff000000;
		break;
	case PIX_FMT_RGBX:
		dpi->pixels[y * dpi->pitch + x] = canonic_xrgb << 8;
		break;
	case PIX_FMT_RGBA:
		dpi->pixels[y * dpi->pitch + x] = canonic_xrgb << 8 | 0xff;
		break;
	case PIX_FMT_XBGR:
		dpi->pixels[y * dpi->pitch + x] = ((canonic_xrgb & 0xff) << 16) | (canonic_xrgb & 0xff00) | ((canonic_xrgb & 0xff0000) >> 16);
		break;
	case PIX_FMT_ABGR:
		dpi->pixels[y * dpi->pitch + x] = ((canonic_xrgb & 0xff) << 16) | (canonic_xrgb & 0xff00) | ((canonic_xrgb & 0xff0000) >> 16) | 0xff000000;
		break;
	case PIX_FMT_BGRX:
		dpi->pixels[y * dpi->pitch + x] = ((canonic_xrgb & 0xff)<<24 | (canonic_xrgb & 0xff00) << 8 | (canonic_xrgb & 0xff0000) >> 8);
		break;
	case PIX_FMT_BGRA:
		dpi->pixels[y * dpi->pitch + x] = ((canonic_xrgb & 0xff) << 24) | ((canonic_xrgb & 0xff00) << 8) | ((canonic_xrgb & 0xff0000) >> 8) | 0xff;
		break;
	}
}

#endif
