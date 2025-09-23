#define ESP324848S040

#include <Arduino.h>
#ifdef ESP324848S040
  #include <lvgl.h>
  #include "../conf/lv_conf.h"
  #include <Arduino_GFX_Library.h>
  #include <TAMC_GT911.h>
  #include "../conf/gfx_lib_conf.h"
  #include <gfx-function.h>
#endif

#ifdef ESP324848S040
  Arduino_DataBus *bus;
  Arduino_ESP32RGBPanel *rgbpanel;
  Arduino_RGB_Display *gfx;
  TAMC_GT911 tp(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));
#endif

const int length = 4; 
Button btns [] = {
{11,10,146,460,20,RGB565(45,45,76),0,0,2,RGB565(0, 255, 254),"Test",false,{{71,140,4,180,20,RGB565(42,200,42),RGB565(180,1,35)},{81,140,4,180,20,RGB565(42,200,42),RGB565(180,1,35)},{61,140,4,180,20,RGB565(42,200,42),RGB565(180,1,35)}}},
{167,10,146,460,20,RGB565(45,45,76),0,0,2,RGB565(0, 255, 254),"Test2",false,{{71,140,4,180,20,RGB565(42,200,42),RGB565(180,1,35)}}},
{323,10,146,460,20,RGB565(45,45,76),0,0,2,RGB565(0, 255, 254),"Test2",false,{}}};


void setup()
{
  Serial.begin(115200); //Инициализация порта отладки
  delay(1000);

  Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
  tp.begin(); // Инициализация сенсорного экрана
  tp.setRotation(TOUCH_GT911_ROTATION);

  bus = new Arduino_SWSPI(
    GFX_NOT_DEFINED /* DC */, TFT_CS, TFT_SCK, TFT_MOSI, GFX_NOT_DEFINED /* MISO */);
  rgbpanel = new Arduino_ESP32RGBPanel(
  TFT_DE, TFT_VSYNC, TFT_HSYNC, TFT_PCLK,
  TFT_R0, TFT_R1, TFT_R2, TFT_R3, TFT_R4,
  TFT_G0, TFT_G1, TFT_G2, TFT_G3, TFT_G4, TFT_G5,
  TFT_B0, TFT_B1, TFT_B2, TFT_B3, TFT_B4,
  1 /* hsync_polarity */, 10 /* hsync_front_porch */, 8 /* hsync_pulse_width */, 50 /* hsync_back_porch */,
  1 /* vsync_polarity */, 10 /* vsync_front_porch */, 8 /* vsync_pulse_width */, 20 /* vsync_back_porch */,
  1,TFT_SPEED
  );

  gfx = new Arduino_RGB_Display(
    max(TFT_MAP_X1, TFT_MAP_X2), max(TFT_MAP_Y1, TFT_MAP_Y2), 
    rgbpanel,TFT_ROTATE,true,bus,GFX_NOT_DEFINED, 
    st7701_type9_init_operations,sizeof(st7701_type9_init_operations));

  gfx->begin();
  gfx->fillScreen(RGB565(11, 12, 66));

  #ifdef GFX_BL
    pinMode(GFX_BL, OUTPUT); //Включение дисплея
    digitalWrite(GFX_BL, HIGH);
  #endif

  for(int i=0; i < length; i++){ 
    displayBTN(gfx,btns[i]); //Начальная отрисовка кнопок
    }

   
}
  
uint32_t ms0 = 0;  
 
void loop() {
  uint32_t ms = millis();
  tp.read();

  if( ms0 == 0 || ms - ms0 > 500 ){ // Убираем дребезг виртуальных кнопок (задержка 0.5 сек)
     if (tp.isTouched){
      ms0 = ms;
      switchBTN(gfx,btns,length,ms0,tp.points[0].x, tp.points[0].y);
     }
  }
}
 