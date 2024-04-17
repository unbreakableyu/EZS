#ifndef _EZS_COLORCYCLING_H_
#define _EZS_COLORCYCLING_H_

#include <cyg/kernel/kapi.h>

/*!
 * @file colorcycling.h
 * @brief A simple color cycling interface.
 * @author Phillip Raffeck
 * \ingroup colorcycling
 */

/** Color encoding in RGB notation.*/
typedef struct color {
	cyg_uint8 r;
	cyg_uint8 g;
	cyg_uint8 b;
} color_t;

#define COLOR_KEYS 15 ///< Number of color keys.
#define FRAMES 4 ///< Number of frames in the animation.

/** A palette is a mapping of a color key to a color. */
typedef struct palette {
	cyg_uint8 mapping[COLOR_KEYS]; ///< Mapping of color keys to colors. For a smaller memory footprint, colors are stored once in the image and only indices are used here.
	struct palette *next; ///< Reference to palette of the next animation frame.
} palette_t;

/**
 * \brief Function type to generate NULL-terminated list of palettes.
 *
 * \return Pointer to the first element of a linked list of palettes.
 *
 * NOTE: The returned list must be freed by the caller.
 */
typedef palette_t* (*palette_generator_t)(void);

/** Description of a colorcycling-animated image. */
typedef struct image {
	size_t width; ///< Image width in pixels.
	size_t height; ///< Image height in pixels.
	size_t num_colors; ///< Number of colors used in image.
	color_t *colors; ///< Colors used in image.
	palette_generator_t generate_palettes; ///< Palette list generator.
	cyg_uint8 *data; ///< Compressed image data, see color_key_for_pixel. Has exactly `width`*`height`/2 entries.
} image_t;

/**
 * \brief Returns the color key of a given pixel.
 *
 * Pixels are stored row-wise.
 * The color key for a pixel is stored in 4 bits (a nibble) of data, meaning each byte of the image data stores the color key for two pixels.
 * Image data starts at the top nibble of a byte (starting from the most significant bit).
 *
 * \param image Image to be drawn, storing color key information.
 * \param col Column position of the pixel.
 * \param row Row position of the pixel.
 * \return Color key for the pixel.
 */
cyg_uint8 color_key_for_pixel(image_t *image, size_t col, size_t row);

/**
 * \brief Converts a color key to a color according to the given palette.
 *
 * \param image Image to be drawn, storing the colors of the image.
 * \param palette Color palette of the current frame.
 * \param color_key Color key.
 * \return Color corresponding to the color key in the current palette.
 */
color_t color_key_to_color(image_t *image, palette_t *palette, cyg_uint8 color_key);

#endif
