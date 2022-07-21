#ifndef GUIButton_H
#define GUIButton_H
#include "Properties/Alignment.h"

#include "GUIComponent.h"
#include <string>
#include <iostream>
namespace RaylibGUIPlus {
 class GUIButton : public GUIComponent
{
public:
	GUIButton(Rectangle rect);
	RaylibGUIPlus::Alignment TextAlignment = Alignment::Left;
	std::string Text = "Button";
	virtual void AdjustmentSize();
	virtual void Render();
};
	 

	GUIButton::GUIButton(Rectangle size)
	{
		this->Rect = size;
	}
	 
	void GUIButton::AdjustmentSize() {
		this->Rect.height = this->Font.baseSize ;
		this->Rect.width= MeasureTextEx(this->Font, this->Text.c_str(), this->Font.baseSize, 0).x;
	}
	void GUIButton::Render()
	{
		this->Event.Reset();
		DrawRectangle(
			this->Rect.x- this->BorderSize,
			this->Rect.y- this->BorderSize,
			this->Rect.width+ (this->BorderSize*2),
			this->Rect.height+ (this->BorderSize*2),
			this->BorderColor);

		DrawRectangle(
			this->Rect.x,
        	this->Rect.y,
			this->Rect.width,
			this->Rect.height,
			this->BackgroundColor);
			Vector2 mousePoint = GetMousePosition();
			this->Event.MouseDown = CheckCollisionPointRec(mousePoint, this->Rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && this->Enable;
		std::string clonetext = this->Text;
		Vector2 textpos;
		textpos = MeasureTextEx(this->Font, clonetext.c_str(), this->Font.baseSize, 0);
			while (textpos.x > this->Rect.width) {
				clonetext.erase(0, 1);
				textpos = MeasureTextEx(this->Font, clonetext.c_str(), this->Font.baseSize, 1);
			}  
		 
		Vector2 startdraw;
		if (this->TextAlignment == Alignment::Center) {
			float posx;
			posx = (this->Rect.width / 2) - (textpos.x / 2);
			posx = posx + this->Rect.x ;
			startdraw = (Vector2)
			{
			posx , this->Rect.y
			};
		}
		else if (this->TextAlignment == Alignment::Right) {
			float posx;
			posx = (this->Rect.width) - (textpos.x);

			posx = posx + this->Rect.x ;

			startdraw = (Vector2)
			{
			posx , this->Rect.y
			};
		}
		else {
			startdraw = (Vector2)
			{
			this->Rect.x  , this->Rect.y
			};
		}
		DrawTextEx(this->Font,
			clonetext.c_str(),
			startdraw, this->Font.baseSize, 0, this->TextColor);

	}

}
#endif










 