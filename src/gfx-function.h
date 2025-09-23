#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <FreeSerif16pt7b.h> //Size 16

struct Ligth {
   int16_t x; 
   int16_t y; 
   int16_t width; 
   int16_t height;
   int16_t radius;  
   int color_on;
   int color_off;
};

struct Button {
   int16_t x; 
   int16_t y; 
   int16_t width; 
   int16_t height;
   int16_t radius;  
   int color; 
   int16_t text_x; 
   int16_t text_y; 
   uint8_t size_text; 
   int color_text;
   const char *name_text;
   bool color_ligth;
   Ligth ligth[10];
};

// GFXfont *font = new GFXfont

// Отображение одной кнопки из структуры
void displayBTN(Arduino_RGB_Display *gfx, Button btn){
    int16_t select_color;

    gfx->fillRoundRect(btn.x,btn.y,btn.width, btn.height,btn.radius,btn.color);  // Fill button
    gfx->setCursor(btn.x+btn.text_x, btn.y+btn.text_y); // Cursor text
    //gfx->setFont(&FreeSerif16pt7b);
//    gfx->setTextSize(btn.size_text);
//    gfx->setTextColor(btn.color_text);
//    gfx->print(btn.name_text);

    int n = sizeof(btn.ligth)/sizeof(btn.ligth[0]);
    if(n){
        for(int x=0; x < n; x++){    
            select_color = btn.color_ligth?btn.ligth[x].color_on:btn.ligth[x].color_off;
            gfx->fillRoundRect(btn.x+btn.ligth[x].x,btn.y+btn.ligth[x].y,btn.ligth[x].width, btn.ligth[x].height,btn.ligth[x].radius,select_color);  // Fill button
        }
    }
}

// //Кнопка переключениея
// void radioBTN(Arduino_RGB_Display *gfx, Button *btns, int length_array, uint32_t ms0, int x, int y){
//         int n_new    = -1;
//         int n_old    = -1;
//         for( int i=0; i<length_array; i++){
//            if( btns[i].ligth.color_ligth )n_old = i; 
//            if( x > btns[i].x && x < btns[i].x+btns[i].width && y > btns[i].y && y < btns[i].y+btns[i].height )n_new = i;
//         }
//         Serial.printf("x=%d y=%d old=%d new=%d ms=%ld\n",x,y,n_old,n_new,ms0);
//         if( n_new >= 0 && n_old == n_new ){ //Если нажата та же кнопка, инвертируем состояние
//            btns[n_new].ligth.color_ligth = !btns[n_new].ligth.color_ligth;
//            displayBTN(gfx, btns[n_new]);
//         }
//         else if( n_new >=0  ){ //Фиксируем нажатую кнопку
//            btns[n_new].ligth.color_ligth = true;
//            displayBTN(gfx, btns[n_new]);
//            if( n_old >= 0 ){ //Убираем предыдущую кнопку
//               btns[n_old].ligth.color_ligth = false;
//               displayBTN(gfx, btns[n_old]);
//            }
//         }
// }

//Кнопка включения и выключения
void switchBTN(Arduino_RGB_Display *gfx, Button *btns, int length_array, uint32_t ms0, int x, int y){
        for( int i=0; i<length_array; i++){
           if( x > btns[i].x && x < btns[i].x+btns[i].width && y > btns[i].y && y < btns[i].y+btns[i].height )
           {
                btns[i].color_ligth = !btns[i].color_ligth;
                displayBTN(gfx, btns[i]);
           }
        }
}