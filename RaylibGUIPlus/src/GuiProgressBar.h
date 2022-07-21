#ifndef GUIProgressBar_H
#define GUIProgressBar_H

#include <cmath>
#include <string>
#include "GUIComponent.h"


namespace RaylibGUIPlus {
	class GUIProgressBar : public GUIComponent
	{
	public:
	
	 
		GUIProgressBar(Rectangle rect);
		 
		 
		 
		Color ProgressColor = DARKGREEN;
		  
		float Value;
		virtual void AdjustmentSize();
		virtual void Render();
	};
	
	GUIProgressBar::GUIProgressBar(Rectangle rect)
	{
		this->Rect = rect;
	}

	void GUIProgressBar::AdjustmentSize() {
		this->Rect.height = this->Font.baseSize;
		this->Rect.width =std::max(this->Rect.width, MeasureTextEx(this->Font, "100%", this->Font.baseSize, 0).x);
	}
	void GUIProgressBar::Render()
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
			this->Rect.x,
			this->Rect.y,
			this->Rect.width* this->Value,
			this->Rect.height,
			this->ProgressColor);
		
		 
		Vector2 textpos;
		std::string valtostr(std::to_string((int)round(this->Value * 100)));
		valtostr = valtostr + "%";
		textpos = MeasureTextEx(this->Font, valtostr.c_str(), this->Font.baseSize, 0);

		Vector2 startdraw;
		float posx;
		posx = (this->Rect.width / 2) - (textpos.x / 2);
		posx = posx + this->Rect.x;
		startdraw = (Vector2)
		{
		posx , this->Rect.y
		};
		 
		DrawTextEx(this->Font,
			valtostr.c_str(),
			startdraw, this->Font.baseSize, 0, this->TextColor);

	}

}
#endif