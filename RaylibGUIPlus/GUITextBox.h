#ifndef GUITextBox_H
#define GUITextBox_H
#include "lib/raylib.h"
#include "Properties/Alignment.h"
#include <string>
#include <iostream>
#include <functional>
 
namespace RaylibGUIPlus {

typedef enum TextBoxType { Text, Password } TextBoxType;

	class GUITextBox
{
public:
	
	GUITextBox();
	GUITextBox(Rectangle rect);
	 
	void AdjustmentHeight();
	Color BackgroundColor = WHITE;
	Color BorderColor = BLACK;
	Color TextColor = BLACK;
	int BorderSize = 1;
	Font Font = GetFontDefault();
	int MaxLength = 25;
	Rectangle Position;
	void Render();
	int ReadOnly = false;
	RaylibGUIPlus::Alignment TextAlignment = Alignment::Left;
	std::string Value = "";
	TextBoxType TextBoxType= TextBoxType::Text;
private:
	bool focus = false;
	std::function<void(GUITextBox*)> callback;
};
	GUITextBox::GUITextBox() {

	}
	GUITextBox::GUITextBox(Rectangle rect)
	{
		this->Position = rect;
	}
	 
	void GUITextBox::AdjustmentHeight() {		 
		this->Position.height = this->Font.baseSize ;
		 	
	}
	void GUITextBox::Render()
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

		if (CheckCollisionPointRec(mousePoint, this->Position) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			this->focus = true;

		}
		else if (!CheckCollisionPointRec(mousePoint, this->Position) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			this->focus = false;
		}

		if (!this->ReadOnly && this->focus) {

			if ((this->Value.length() < (this->MaxLength - 1)) && (!IsKeyPressed(KEY_BACKSPACE))) {

				int key = GetCharPressed();
				if (key > 0) {
					int byteSize = 0;
					const char* textUTF8 = CodepointToUTF8(key, &byteSize);
					for (int i = 0; i < byteSize; i++)
					{
						this->Value = this->Value + textUTF8[i];
					}

				}

			}
			else if (IsKeyPressed(KEY_BACKSPACE) && this->Value.length() > 0) {
				this->Value.pop_back();
			}
			if (IsKeyPressed(KEY_ENTER)) {
			 
			}
		}
		std::string clonetext = "";
		if (this->TextBoxType == TextBoxType::Text) {
			clonetext = this->Value;
		} else if (this->TextBoxType == TextBoxType::Password) {
			 clonetext.append(this->Value.length(), '*');
		}
		
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

		startdraw.x = startdraw.x + textpos.x ;
		if (!this->ReadOnly && this->focus) {
			if (this->TextAlignment == Alignment::Right) {
				startdraw.x = this->Position.x +this->Position.width;
			}
			DrawLineEx(startdraw, (Vector2) { startdraw.x, startdraw.y + textpos.y }, this->Font.baseSize*0.1, this->TextColor);
			
		}


	}

}
#endif










 