#ifndef GUIScrollBar_H
#define GUIScrollBar_H

#include <cmath>
#include <string>
 
#include "Properties/Orientation.h"
#include "GUIComponent.h"

namespace RaylibGUIPlus {
	class GUIScrollBar: public GUIComponent
	{
	public:		 
	
		GUIScrollBar(Rectangle rect);
		Color ScrollColor = DARKGREEN;
		Color TextColor = BLACK;
		float Min = 0;
		float Max = 1;
		float Value=0;
		 
		virtual void Render();
	private:
		Orientation orientation = Orientation::Horizontal;
		Rectangle slider;

	};
	
	GUIScrollBar::GUIScrollBar(Rectangle rect)
	{
		this->Rect = rect;
	 
		this->slider.x=	this->Rect.x;
		this->slider.y=this->Rect.y;
		this->slider.width=this->Rect.width;
		this->slider.height=this->Rect.height;
		
		
		if (rect.width <= rect.height) {
			this->orientation = Orientation::Vertical;
			this->slider.height=12;
		}
		else {
			this->orientation = Orientation::Horizontal;			
			this->slider.width=12;
		}
		
	}

 
	void GUIScrollBar::Render()
	{
	 
		DrawRectangle(
			this->Rect.x - this->BorderSize,
			this->Rect.y - this->BorderSize,
			this->Rect.width + (this->BorderSize * 2),
			this->Rect.height + (this->BorderSize * 2),
			this->BorderColor);

		DrawRectangle(
			this->Rect.x,
			this->Rect.y,
			this->Rect.width,
			this->Rect.height,
			this->BackgroundColor);

		DrawRectangle(
				this->slider.x,
				this->slider.y,
				this->slider.width ,
				this->slider.height,
				this->ScrollColor);
	 
		if (this->orientation == Orientation::Horizontal) {
			this->slider.x = this->Rect.x +  (((float)(this->Value - this->Min) / this->Max - this->Min) * (this->Rect.width - this->slider.width));
		}
		else {	  
			this->slider.y = this->Rect.y + (((float)(this->Value - this->Min) / this->Max - this->Min) * (this->Rect.height - this->slider.height));
		}
		Vector2 mousePoint = GetMousePosition();
		this->Event.MouseDown = CheckCollisionPointRec(mousePoint, this->Rect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && this->Enable;
		if (this->Event.MouseDown) {
			if (this->orientation == Orientation::Horizontal) {
				this->Value = (int)(((float)(mousePoint.x - this->Rect.x - slider.width / 2) * this->Max - this->Min) / (this->Rect.width - slider.width) + this->Min);
			}
			else {
				this->Value = (int)(((float)(mousePoint.y - this->Rect.y - slider.height / 2) * this->Max - this->Min) / (this->Rect.height - slider.height) + this->Min);
			}
		}
		if (this->Value > this->Max) this->Value = this->Max;
		if (this->Value < this->Min) this->Value = this->Min;

	}

}
#endif