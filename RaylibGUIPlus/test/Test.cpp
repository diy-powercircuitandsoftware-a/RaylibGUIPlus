 
 
#include "../src/GuiDropDownBox.h"
 //#include "raygui.h"
#include "raylib.h"
#include <iostream>

int main()
{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "raylib=>RaylibGUIPlus Test");
    RaylibGUIPlus::GuiDropDownBox combo= RaylibGUIPlus::GuiDropDownBox(Rectangle{ 20,20,400,100 });
   
    combo.Font = LoadFontEx("test/font/opensans/OpenSans-Regular.ttf", 35, 0, 0);
    combo.AdjustmentHeight();
     combo.AddListItem(RaylibGUIPlus::ListItem{1,"1"});
     combo.AddListItem(RaylibGUIPlus::ListItem{ 2,"2" });
     combo.AddListItem(RaylibGUIPlus::ListItem{ 3,"3" });
    combo.TextAlignment = RaylibGUIPlus::Alignment::Center;
    
    SetTargetFPS(60);              
    while (!WindowShouldClose())    
    {
          
       
       
        BeginDrawing();
        ClearBackground(WHITE);
        
        combo.Render();
       
         
        EndDrawing();
       
        
    }

     CloseWindow();       
   
    return 0;
}
 