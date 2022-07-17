#ifndef GuiProgressBar_H
#define GuiProgressBar_H
#include "raylib.h"
#include <cmath>
#include <string>


namespace RaylibGUIPlus {
	class GuiProgressBar
	{
	public:
		GuiProgressBar();
		~GuiProgressBar();
		GuiProgressBar(Rectangle rect);
		void AdjustmentSizes();
		Color BackgroundColor = RAYWHITE;
		Color BorderColor = BLACK;
		int BorderSize = 1;
		Font Font = GetFontDefault();
		Rectangle Position;
		Color ProgressColor = DARKGREEN;
		void Render();
		Color TextColor = BLACK;
		float Value;
	};
	GuiProgressBar::GuiProgressBar() {

	}
	GuiProgressBar::~GuiProgressBar() {
		UnloadFont(this->Font);
	}
	GuiProgressBar::GuiProgressBar(Rectangle rect)
	{
		this->Position = rect;
	}

	void GuiProgressBar::AdjustmentSizes() {
		this->Position.height = this->Font.baseSize;
		this->Position.width =std::max(this->Position.width, MeasureTextEx(this->Font, "100%", this->Font.baseSize, 0).x);
	}
	void GuiProgressBar::Render()
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
			this->Position.x,
			this->Position.y,
			this->Position.width* this->Value,
			this->Position.height,
			this->ProgressColor);
		
		 
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