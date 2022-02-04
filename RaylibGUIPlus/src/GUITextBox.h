#ifndef GUITextBox_H
#define GUITextBox_H
#include "raylib.h"
#include "Properties/Alignment.h"
#include "Properties/Event.h"
#include <string>
#include <iostream>
#include <regex>

 
namespace RaylibGUIPlus {

typedef enum TextBoxType { Text, Password,Number } TextBoxType;

	class GUITextBox
{
public:
	
	GUITextBox();
	GUITextBox(Rectangle rect);	 
	void AdjustmentHeight();
	Color BackgroundColor = WHITE;
	Color BorderColor = BLACK;
	Event Event;
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
			bool collision = CheckCollisionPointRec(mousePoint, this->Position);
			bool mousepress = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
		if (collision && mousepress) {
			this->focus = true;
			
		}
		else if (!collision && mousepress) {
			this->focus = false;
		}
		this->Event.MouseDown = collision && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
		this->Event.KeyDown = false;
		if (!this->ReadOnly && this->focus) {

			if ((this->Value.length() < (this->MaxLength - 1)) && (!IsKeyPressed(KEY_BACKSPACE))) {

				int key = GetCharPressed();
				if (key > 0) {
					int byteSize = 0;
					const char* textUTF8 = CodepointToUTF8(key, &byteSize);
					for (int i = 0; i < byteSize; i++)
					{
						if (this->TextBoxType == TextBoxType::Number) {
							if (isdigit(textUTF8[i])) {
								this->Value = this->Value + textUTF8[i];
							}
							
						}
						else {
							this->Value = this->Value + textUTF8[i];
						}
						
					}
					
				}
				 this->Event.KeyDown = key > 0;

			}
			else if (IsKeyPressed(KEY_BACKSPACE) && this->Value.length() > 0) {
				this->Value.pop_back();
				this->Event.KeyDown = true;
			}
			if ((IsKeyDown(KEY_LEFT_CONTROL)|| IsKeyDown(KEY_RIGHT_CONTROL))&& IsKeyPressed(KEY_V)) {
				std::string input= GetClipboardText();
				if (this->TextBoxType==TextBoxType::Number) {	
					if (input != "") {
						std::regex integer("(\\+|-)?[[:digit:]]+");
						if (regex_match(input, integer)) {
							this->Value = this->Value+ input;
						}
						else {
							return;
						}
					}
					 
				}
				else {
					this->Value = this->Value+input;
				}
				
				do {
						this->Value.pop_back();
				} while (this->Value.length()>0 &&this->Value.length() > this->MaxLength-1);
			  
			}
			else if ((IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) && IsKeyPressed(KEY_C)&& !TextBoxType::Password) {				 
				SetClipboardText(this->Value.c_str());
			}
		
		}
		std::string clonetext = "";
		if (this->TextBoxType == TextBoxType::Password) {
			clonetext.append(this->Value.length(), '*');
		}
		else {
			clonetext = this->Value;
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










 