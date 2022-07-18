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
		void Render();
		Color ScrollColor = DARKGREEN;
		Color TextColor = BLACK;
		float Min = 0;
		float Max = 1;
		float Value=0;
	private:
		Orientation orientation = Orientation::Horizontal;
		Rectangle slider;

	};
	GuiScrollBar::GuiScrollBar() {
		
	}
	GuiScrollBar::~GuiScrollBar() {
		UnloadFont(this->Font);
	}
	GuiScrollBar::GuiScrollBar(Rectangle rect)
	{
		this->Position = rect;
	 
		this->slider.x=	this->Position.x;
		this->slider.y=this->Position.y;
		this->slider.width=this->Position.width;
		this->slider.height=this->Position.height;
		
		
		if (rect.width <= rect.height) {
			this->orientation = Orientation::Vertical;
			this->slider.height=12;
		}
		else {
			this->orientation = Orientation::Horizontal;			
			this->slider.width=12;
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

		DrawRectangle(
				this->slider.x,
				this->slider.y,
				this->slider.width ,
				this->slider.height,
				this->ScrollColor);
	 
		if (this->orientation == Orientation::Horizontal) {
			this->slider.x = this->Position.x +  (((float)(this->Value - this->Min) / this->Max - this->Min) * (this->Position.width - this->slider.width));
		}
		else {	  
			this->slider.y = this->Position.y + (((float)(this->Value - this->Min) / this->Max - this->Min) * (this->Position.height - this->slider.height));
		}
		Vector2 mousePoint = GetMousePosition();
		this->Event.MouseDown = CheckCollisionPointRec(mousePoint, this->Position) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && this->Enable;
		if (this->Event.MouseDown) {
			if (this->orientation == Orientation::Horizontal) {
				this->Value = (int)(((float)(mousePoint.x - this->Position.x - slider.width / 2) * this->Max - this->Min) / (this->Position.width - slider.width) + this->Min);
			}
			else {
				this->Value = (int)(((float)(mousePoint.y - this->Position.y - slider.height / 2) * this->Max - this->Min) / (this->Position.height - slider.height) + this->Min);
			}
		}
		if (this->Value > this->Max) this->Value = this->Max;
		if (this->Value < this->Min) this->Value = this->Min;

	}

}
#endif