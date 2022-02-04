 
#include "lib/raylib.h"
#include "GUITextBox.h"
#include <iostream>

int main()
{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "raylib=>RaylibGUIPlus Test");
    RaylibGUIPlus::GUITextBox textbox1= RaylibGUIPlus::GUITextBox(Rectangle{ 20,20,400,100 });
    RaylibGUIPlus::GUITextBox textbox2 = RaylibGUIPlus::GUITextBox(Rectangle{ 100,100,400,100 });
    
    
    textbox1.Font = LoadFontEx("../font/opensans/OpenSans-Regular.ttf", 35, 0, 0);
    textbox1.TextAlignment = RaylibGUIPlus::Alignment::Left;
    textbox1.AdjustmentHeight();
    textbox2.Font = LoadFontEx("../font/opensans/OpenSans-Regular.ttf", 35, 0, 0);
    textbox2.TextAlignment = RaylibGUIPlus::Alignment::Center;
    textbox1.BorderSize = 20;
    textbox2.AdjustmentHeight();
    textbox1.TextBoxType = RaylibGUIPlus::TextBoxType::Password;
    
    SetTargetFPS(60);              
    while (!WindowShouldClose())    
    {
       
        BeginDrawing();
        ClearBackground(RAYWHITE);
        textbox1.Render();
        textbox2.Render();
        EndDrawing();
        
    }

     CloseWindow();       
   
    return 0;
}
 