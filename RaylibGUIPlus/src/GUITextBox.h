#ifndef GUITextBox_H
#define GUITextBox_H

#include "Properties/Alignment.h"
 
#include <string>
#include <iostream>
#include <regex>
#include "GUIComponent.h"

 
namespace RaylibGUIPlus {

typedef enum TextBoxType { Text, Password,Number } TextBoxType;

	class GUITextBox : public GUIComponent
{
public:
	
	 
	GUITextBox(Rectangle rect);	 
	 
  
	int MaxLength = 25;
	 
 
 
	RaylibGUIPlus::Alignment TextAlignment = Alignment::Left;
	TextBoxType TextBoxType= TextBoxType::Text;
	Color TextColor = BLACK;
	std::string Value = "";
	virtual void AdjustmentSize();
	virtual void Render();

private:
	bool focus = false;
	 
};

	
	GUITextBox::GUITextBox(Rectangle rect)
	{
		this->Rect = rect;
	}
	 
	void GUITextBox::AdjustmentSize() {
		this->Rect.height = this->Font.baseSize ;		 	
	}
	void GUITextBox::Render()
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
			bool collision = CheckCollisionPointRec(mousePoint, this->Rect);
			bool mousepress = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
		if (collision && mousepress) {
			this->focus = true;
			
		}
		else if (!collision && mousepress) {
			this->focus = false;
		}
		this->Event.MouseDown = collision && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
		 
		if (!this->Enable && this->focus) {

			if ((this->Value.length() < (this->MaxLength - 1)) && (!IsKeyDown(KEY_BACKSPACE))) {

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
						std::regex integer("(\\+|-)?[[:digit:]]+");
						if (regex_match(input, integer)) {
							this->Value = this->Value + input;						
						}
				}
				else {
					this->Value = this->Value+input;
				}
				while (this->Value.length() > 0 && this->Value.length() > this->MaxLength - 1) {
					this->Value.pop_back();
				}
			 
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

		startdraw.x = startdraw.x + textpos.x ;
		if (this->Enable && this->focus) {
			if (this->TextAlignment == Alignment::Right) {
				startdraw.x = this->Rect.x +this->Rect.width;
			}
			DrawLineEx(startdraw, (Vector2) { startdraw.x, startdraw.y + textpos.y }, this->Font.baseSize*0.1, this->TextColor);

		}


	}

}
#endif










 