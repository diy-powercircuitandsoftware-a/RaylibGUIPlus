#ifndef GUICheckBox_H
#define GUICheckBox_H
#include "raylib.h"
#include "Properties/Event.h"
#include <string>
#include <iostream>
 
 
namespace RaylibGUIPlus {
	class GUICheckBox
{
public:
	
	GUICheckBox();
	~GUICheckBox();
	GUICheckBox(Vector2 pos);
	Color BackgroundColor = WHITE;
	Color BorderColor = BLACK;
	int BorderSize = 1;
	bool Checked = false;
	bool Enable = true;
	Event Event;
	Font Font = GetFontDefault();
	Vector2 Position;
	void Render();
	std::string Text = "";
	Color TextColor = BLACK;
 
};
	GUICheckBox::GUICheckBox() {

	}
	GUICheckBox::~GUICheckBox() {
		UnloadFont(this->Font);
	}
	GUICheckBox::GUICheckBox(Vector2 pos)
	{
		this->Position = pos;
	}
	 
	 
	void GUICheckBox::Render()
	{
		this->Event.Reset();
		Vector2 XSize = MeasureTextEx(this->Font,"X", this->Font.baseSize, 0);
		Rectangle realchkbox;
		realchkbox.x = this->Position.x;
		realchkbox.y = this->Position.y;
		realchkbox.width = XSize.y;
		realchkbox.height = XSize.y;
		DrawRectangle(
			realchkbox.x - this->BorderSize,
			realchkbox.y - this->BorderSize,
			realchkbox.width + (this->BorderSize*2),
			realchkbox.height + (this->BorderSize*2),
			this->BorderColor);

		DrawRectangle(
			realchkbox.x,
			realchkbox.y,
			realchkbox.width,
			realchkbox.height,
			this->BackgroundColor);
			Vector2 mousePoint = GetMousePosition();

			this->Event.MouseDown = CheckCollisionPointRec(mousePoint, realchkbox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && this->Enable;
		 
			if (this->Event.MouseDown) {
				this->Checked = !this->Checked;
			}

			if (this->Checked) {
			 DrawLineEx(
					(Vector2){
						realchkbox.x,
						realchkbox.y
					},
					(Vector2){
						realchkbox.x + realchkbox.width,
						realchkbox.y + realchkbox.height
					},
					this->BorderSize*4,
					this->BorderColor
				);
			  
				DrawLineEx(
					(Vector2){
					realchkbox.x , realchkbox.y + realchkbox.height
					},
					(Vector2){
					realchkbox.x + realchkbox.width, realchkbox.y
					},
					this->BorderSize*4 ,
					this->BorderColor
				);
			}
			DrawTextEx(this->Font,
				this->Text.c_str(),
				(Vector2) {
				realchkbox.x + realchkbox.width,
				realchkbox.y  
				}, this->Font.baseSize, 0, this->TextColor);

	}

}
#endif










 