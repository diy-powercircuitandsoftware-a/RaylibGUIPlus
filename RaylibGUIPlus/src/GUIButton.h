#ifndef GUIButton_H
#define GUIButton_H
#include "raylib.h"
#include "Properties/Alignment.h"
#include "Properties/Event.h"
#include <string>
#include <iostream>
 
 
namespace RaylibGUIPlus {
 

	class GUIButton
{
public:
	
	GUIButton();
	GUIButton(Rectangle rect);
	 
	void AdjustmentSizes();
	Color BackgroundColor = RAYWHITE;
	Color BorderColor = BLACK;
	Event Event;
	Color TextColor = BLACK;
	int BorderSize = 1;
	Font Font = GetFontDefault();
	 
	Rectangle Position;
	void Render();
	int Enable = true;
	RaylibGUIPlus::Alignment TextAlignment = Alignment::Left;
	std::string Text = "Button";
 
};
	GUIButton::GUIButton() {

	}
	GUIButton::GUIButton(Rectangle rect)
	{
		this->Position = rect;
	}
	 
	void GUIButton::AdjustmentSizes() {
		this->Position.height = this->Font.baseSize ;
		this->Position.width= MeasureTextEx(this->Font, this->Text.c_str(), this->Font.baseSize, 0).x;
	}
	void GUIButton::Render()
	{
		DrawRectangle(
			this->Position.x- this->BorderSize,
			this->Position.y- this->BorderSize,
			this->Position.width+ (this->BorderSize*2),
			this->Position.height+ (this->BorderSize*2),
			this->BorderColor);

		DrawRectangle(
			this->Position.x,
			this->Position.y,
			this->Position.width,
			this->Position.height,
			this->BackgroundColor);
			Vector2 mousePoint = GetMousePosition();
			this->Event.MouseDown = CheckCollisionPointRec(mousePoint, this->Position) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && this->Enable; 
		std::string clonetext = this->Text;
		Vector2 textpos;
		textpos = MeasureTextEx(this->Font, clonetext.c_str(), this->Font.baseSize, 0);

		if (textpos.x > this->Position.width) {
			do {
				clonetext.erase(0, 1);
				textpos = MeasureTextEx(this->Font, clonetext.c_str(), this->Font.baseSize, 1);
			} while (textpos.x > this->Position.width);
		}
		Vector2 startdraw;
		if (this->TextAlignment == Alignment::Center) {
			float posx;
			posx = (this->Position.width / 2) - (textpos.x / 2);
			posx = posx + this->Position.x ;
			startdraw = (Vector2)
			{
			posx , this->Position.y 
			};
		}
		else if (this->TextAlignment == Alignment::Right) {
			float posx;
			posx = (this->Position.width) - (textpos.x);

			posx = posx + this->Position.x ;

			startdraw = (Vector2)
			{
			posx , this->Position.y  
			};
		}
		else {
			startdraw = (Vector2)
			{
			this->Position.x  , this->Position.y 
			};
		}
		DrawTextEx(this->Font,
			clonetext.c_str(),
			startdraw, this->Font.baseSize, 0, this->TextColor);

	}

}
#endif










 