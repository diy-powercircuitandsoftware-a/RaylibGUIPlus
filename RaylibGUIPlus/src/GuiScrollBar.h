#ifndef GuiScrollBar_H
#define GuiScrollBar_H
#include "raylib.h"
#include <cmath>
#include <string>
#include "Properties/Event.h"
#include "Properties/Orientation.h"


namespace RaylibGUIPlus {
	class GuiScrollBar
	{
	public:
		 
		GuiScrollBar();
		~GuiScrollBar();
		GuiScrollBar(Rectangle rect);
		void AdjustmentSizes();		
		Color BackgroundColor = RAYWHITE;
		int BorderSize = 1;
		Color BorderColor = BLACK;
		bool Enable = true;
		Event Event;
		Font Font = GetFontDefault();
	
		
		Rectangle Position;
		Color ProgressColor = DARKGREEN;
		void Render();
		Color TextColor = BLACK;
		float Min = 0;
		float Max = 1;
		float Value=0;
	private:
		Orientation orientation = Orientation::Horizontal;

	};
	GuiScrollBar::GuiScrollBar() {
		
	}
	GuiScrollBar::~GuiScrollBar() {
		UnloadFont(this->Font);
	}
	GuiScrollBar::GuiScrollBar(Rectangle rect)
	{
		this->Position = rect;
		bool isVertical = (rect.width > rect.height) ? false : true;
		if (isVertical) {
			this->orientation = Orientation::Vertical;
		}
		else {
			this->orientation = Orientation::Horizontal;
		}
	}

	void GuiScrollBar::AdjustmentSizes() {
		this->Position.height = this->Font.baseSize;
		this->Position.width =std::max(this->Position.width, MeasureTextEx(this->Font, "^", this->Font.baseSize, 0).x);
	}
	void GuiScrollBar::Render()
	{
	 
		DrawRectangle(
			this->Position.x - this->BorderSize,
			this->Position.y - this->BorderSize,
			this->Position.width + (this->BorderSize * 2),
			this->Position.height + (this->BorderSize * 2),
			this->BorderColor);

		DrawRectangle(
			this->Position.x,
			this->Position.y,
			this->Position.width,
			this->Position.height,
			this->BackgroundColor);

		if (this->orientation == Orientation::Horizontal) {
			DrawRectangle(
				this->Position.x,
				this->Position.y,
				this->Position.width * (this->Value / this->Max),
				this->Position.height,
				this->ProgressColor);
		}
		else {
			DrawRectangle(
				this->Position.x,
				this->Position.y,
				this->Position.width ,
				this->Position.height * (this->Value / this->Max),
				this->ProgressColor);
		}
		Vector2 mousePoint = GetMousePosition();
		this->Event.MouseDown = CheckCollisionPointRec(mousePoint, this->Position) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && this->Enable;
		if (this->Event.MouseDown) {
			if (this->orientation == Orientation::Horizontal) {
				//this->Value = (int)(((float)(mousePoint.x - scrollArea.x - slider.width / 2) * this->Max-this->Min) / (scrollArea.width - slider.width) + minValue);
			}
			else {

			}
		}
		return;
		Vector2 textpos;
		std::string valtostr(std::to_string((int)round(this->Value * 100)));
		valtostr = valtostr + "%";
		 textpos = MeasureTextEx(this->Font, valtostr.c_str(), this->Font.baseSize, 0);

		
		 

		Vector2 startdraw;
		float posx;
		posx = (this->Position.width / 2) - (textpos.x / 2);
		posx = posx + this->Position.x;
		startdraw = (Vector2)
		{
		posx , this->Position.y
		};
		 
		DrawTextEx(this->Font,
			valtostr.c_str(),
			startdraw, this->Font.baseSize, 0, this->TextColor);

	}

}
#endif