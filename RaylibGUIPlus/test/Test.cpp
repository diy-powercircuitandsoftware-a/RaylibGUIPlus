 
#include "raylib.h"
#include "../src/GUITextBox.h"
#include "../src/GUIButton.h"
#include "../src/GUICheckbox.h"
#include <iostream>

int main()
{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "raylib=>RaylibGUIPlus Test");
    RaylibGUIPlus::GUITextBox textbox1= RaylibGUIPlus::GUITextBox(Rectangle{ 20,20,400,100 });
    RaylibGUIPlus::GUIButton button1 = RaylibGUIPlus::GUIButton(Rectangle{ 100,100,400,100 });
    RaylibGUIPlus::GUICheckbox chkbox1 = RaylibGUIPlus::GUICheckbox(Vector2{100,100});

    
    textbox1.Font = LoadFontEx("test/font/opensans/OpenSans-Regular.ttf", 35, 0, 0);
    button1.Font = LoadFontEx("test/font/opensans/OpenSans-Regular.ttf", 35, 0, 0);
    chkbox1.Font = LoadFontEx("test/font/opensans/OpenSans-Regular.ttf", 35, 0, 0);
    button1.TextAlignment = RaylibGUIPlus::Alignment::Center;
    textbox1.TextBoxType = RaylibGUIPlus::TextBoxType::Number;
    
    
    button1.AdjustmentSizes();
    button1.Enable = true;


    SetTargetFPS(60);              
    while (!WindowShouldClose())    
    {
         RaylibGUIPlus::Event e = textbox1.Event;
         if (e.KeyDown) {
             std::cout << textbox1.Value;
         }
        
       
        BeginDrawing();
        ClearBackground(RAYWHITE);
        textbox1.Render();
        button1.Render();
      //  chkbox1.Render();
        EndDrawing();
        
    }

     CloseWindow();       
   
    return 0;
}
 