/* ========================================
 *
 * Copyright Arachnid Labs, 2013
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#define FONT_GLYPH_PAGES 2
#define FONT_GLYPH_COLUMNS 12
#define FONT_GLYPH_COUNT 192
#define FONT_GLYPH_OFFSET 32
#define FONT_BIGDIGIT_WIDTH 24
#define FONT_BIGDIGIT_STEP 96

#define GLYPH_CHAR(x) (x[0])
#define FONT_GLYPH_OHM "\x7F"   //125+32
#define FONT_GLYPH_LARR "\x80"  //126+32
#define FONT_GLYPH_RARR "\x81"  //127+32
#define FONT_GLYPH_UARR "\x82"  //158+32
#define FONT_GLYPH_DARR "\x83"  //159+32
#define FONT_GLYPH_BIGPERIOD "\x84" //190+32
#define FONT_GLYPH_ENTER "\x85" //ENTER 191+32
#define FONT_GLYPH_MENU_LARR "\x86" //ENTER 192+32
#define FONT_GLYPH_MENU_RARR "\x87" //ENTER 193+32
#define FONT_GLYPH_GOOD_COOLER "\x88" //ENTER 194+32
#define FONT_GLYPH_BAD_COOLER "\x89" //ENTER 195+32
#define FONT_GLYPH_CELSIUS "\x8A" //ENTER 196+32

extern const char glyphs[107][FONT_GLYPH_PAGES][FONT_GLYPH_COLUMNS];
extern const char big_glyphs[10][FONT_BIGDIGIT_STEP];
extern const char big_period[5];
/* [] END OF FILE */
