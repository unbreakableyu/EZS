#include <cyg/hal/hal_arch.h>
#include <cyg/kernel/kapi.h>
#include <cyg/infra/diag.h>

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <iso646.h>

#include "ezs_dac.h"
#include "ezs_gpio.h"
#include "ezs_delay.h"
#include "ezs_counter.h"
#include "ezs_io.h"
#include "ezs_serial.h"

#include "ezs_fb.h"
#include "ezs_lcd.h"

#include "colorcycling.h"

#ifdef SANITY_TEST
#include "ezs_test.h"
#endif



/* Thread-Stack */
#define STACKSIZE CYGNUM_HAL_STACK_SIZE_MINIMUM+2048
static cyg_uint8 my_stack[STACKSIZE];
	//cyg_uint8 eCos的数据类型 类似于 unsigned char
	//stack数组
	//my_stack[STACKSIZE] 定义了一个数组，其大小为 STACKSIZE。这个数组用作之后创建线程时的堆栈空间，存储线程的局部变量、函数调用返回地址等。
static cyg_handle_t handle;
	//线程句柄
static cyg_thread   threaddata;



// Image data for a colorcycling animation of the chair's logo.
#include "i4logo_animated.c"
extern image_t logo;

cyg_uint8 color_key_for_pixel(image_t *image, size_t col, size_t row) {
	/*
	 * TODO:
	 * - Index für Pixel berechnen.
	 * - Korrektes Nibble aus Byte extrahieren.
	 * */
	return 0;
}

color_t color_key_to_color(image_t *image, palette_t *palette, cyg_uint8 color_key) {
	/* TODO: Farbe des Schlüssels aus der aktuellen Palette bestimmen. */
	return (color_t){0,0,0};
}

void ezs_plot_animation(void) {
	pixel *const fb     = ezs_lcd_get_fb();
	const size_t x_offset = 110;
	const size_t y_offset = 10;
	/*
	 * TODO: Logo (image_t logo) an vorgegebener Position (x_offset, y_offset) pixelweise zeichnen:
	 * 1. Farbschlüssel für Pixel (x, y) im Bild nachschlagen
	 * 2. Farbschlüssel gemäß Palette in Farbe übersetzen
	 * 3. Pixel mit ermittelter Farbe malen
	 * Am Ende: Palette für den nächsten Durchgang aktualisieren.
	 * */
}

/**
 * \brief Computes the displacement of a sine wave at a given point in time.
 *
 * \param frequency Wave frequency in Hz.
 * \param amplitude Amplitude, unitless.
 * \param phase Initial phase angle of the wave, given in radians.
 * \param y_offset Vertical offset of the wave, unitless.
 * \param t_us Point in time at which the displacement shall be calculated, given in microseconds.
 */
float sine_wave(const float frequency, const float amplitude, const float phase, const float y_offset, const unsigned int t_us) {
	return 0.f;
}

void test_thread(cyg_addrword_t arg)
{
	ezs_printf("Hallo Welt!\n");
	/* Einmalige Aufgaben ... */
	/* TODO: Liste von Paletten generieren. */

	while(1)
	{
		/* Periodische Aufgaben ... */
	}
}

void cyg_user_start(void)
{
	ezs_gpio_init();
	ezs_counter_init();
	ezs_serial_init();
	ezs_lcd_init();
	ezs_fb_init();
	ezs_dac_init();

#ifdef SANITY_TEST
	ezs_sanity_test();
#endif

	/* Thread erzeugen ... */
    cyg_thread_create       // normalerweise after oder included in init

        (
            10,             // Threadpriorität, not sure 10 (höh 0, 0-31)
            test_thread,    // Thread function: ezs_printf("Hallo Welt!\n");
            0,              // Entry Data, Parameter passed to the thread function
            "Hello Thread", // Threadname
            my_stack,       // Basisadresse des Threadstacks
            STACKSIZE,      // Stackgröße in Bytes
            &handle,        // Eindeutiger Identifikator
            &threaddata
        );
	/* Thread starten ... */
	cyg_thread_resume(&threaddata);
}


