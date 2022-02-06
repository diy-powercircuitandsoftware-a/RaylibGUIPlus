#ifndef GuiDropDownBox_H
#define GuiDropDownBox_H
#include "raylib.h"
#include "Properties/Alignment.h"
#include "Properties/Event.h"
#include <string>
#include <iostream>
#include <vector>
#include "DataUI/ListItem.h"

 
namespace RaylibGUIPlus {
	class GuiDropDownBox
{
public:
	
	GuiDropDownBox();
	GuiDropDownBox(Rectangle rect);
	void  AddListItem(ListItem l);
	void  AdjustmentHeight();
	Color BackgroundColor = RAYWHITE;
	Color BorderColor = BLACK;
	Color HoverColor = BLUE;
	Event Event;
	Color TextColor = BLACK;
	int BorderSize = 1;
	Font Font = GetFontDefault(); 
	Rectangle Position;
	void Render();
	int ReadOnly = false;
	RaylibGUIPlus::Alignment TextAlignment = Alignment::Left;
	ListItem Value ;
	 
private:
	bool toggle = false;
	std::vector<ListItem> list;
	Vector2 DrawAlignment(Rectangle rect,std::string s);
	 
};
	GuiDropDownBox::GuiDropDownBox() {

	}
	GuiDropDownBox::GuiDropDownBox(Rectangle rect)
	{
		this->Position = rect;
	}
	void GuiDropDownBox::AddListItem(ListItem l) {  
		this->list.push_back(l);
		this->Value = l;
	}
	void GuiDropDownBox::AdjustmentHeight() {
		this->Position.height = this->Font.baseSize ;
	}
	Vector2 GuiDropDownBox::DrawAlignment(Rectangle rect, std::string s ) {
		  
		Vector2 textpos;
		textpos = MeasureTextEx(this->Font, s.c_str(), this->Font.baseSize, 0);

		while (textpos.x > rect.width) {
			s.erase(0, 1);
			textpos = MeasureTextEx(this->Font, s.c_str(), this->Font.baseSize, 1);
		}

		Vector2 startdraw;
		if (this->TextAlignment == Alignment::Center) {

			float posx;
			posx = (rect.width / 2) - (textpos.x / 2);

			posx = posx + rect.x;

			startdraw = (Vector2)
			{
			posx , rect.y
			};
		}
		else if (this->TextAlignment == Alignment::Right) {
			float posx;
			posx = (rect.width) - (textpos.x);

			posx = posx + rect.x;

			startdraw = (Vector2)
			{
			posx , rect.y
			};
		}
		else {
			startdraw = (Vector2)
			{
			rect.x  ,rect.y
			};
		}

		DrawTextEx(this->Font,
			s.c_str(),
			startdraw, this->Font.baseSize, 0, this->TextColor);

		return textpos;
	}
	void GuiDropDownBox::Render()
	{
		this->Event.Reset();
		int vtextposx = MeasureTextEx(this->Font, "V", this->Font.baseSize, 0).x*1.2;

		DrawRectangle(
			this->Position.x- this->BorderSize,
			this->Position.y- this->BorderSize,
			this->Position.width+ vtextposx + (this->BorderSize*2),
			this->Position.height+ (this->BorderSize*2),
			this->BorderColor);
			
		DrawTextEx(this->Font,
			"V",
			(Vector2){
			this->Position.x+ this->Position.width+ (this->BorderSize * 2),
				this->Position.y
			}, this->Font.baseSize, 0, this->BackgroundColor);
	 
		DrawRectangle(
			this->Position.x,
			this->Position.y,
			this->Position.width,
			this->Position.height,
			this->BackgroundColor);
			Vector2 mousepoint = GetMousePosition();
			this->Position.width = this->Position.width + vtextposx;
			bool collision = CheckCollisionPointRec(mousepoint, this->Position);
			bool mousepress = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
			 
		if (collision && mousepress&& !this->ReadOnly) {
			this->toggle = !this->toggle;
		}else if (collision && mousepress && this->ReadOnly) {
			this->toggle = false;
		}
		 
		this->Event.MouseDown = collision && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
		this->Position.width = this->Position.width - vtextposx;
		 
		Vector2 textpos = this->DrawAlignment(this->Position, this->Value.text);

		if (this->toggle) {
			Rectangle listposition=this->Position;
			listposition.y = listposition.y + textpos.y;
			listposition.width = listposition.width + vtextposx;
			DrawRectangle(
				listposition.x- this->BorderSize,
				listposition.y- this->BorderSize,
				listposition.width+ (this->BorderSize*2),
				(listposition.height* this->list.size()) + ((this->BorderSize+1) * 2),
				this->BorderColor);
			for (int i = 0; i < this->list.size(); i++) {
				bool listcollision = CheckCollisionPointRec(mousepoint, listposition);
				Color bg = this->BackgroundColor;
				if (listcollision) {
					 bg = this->HoverColor;
				}
				if (listcollision&&mousepress) {
					this->Value = this->list.at(i);
					this->toggle = false;
					break;
				}
				DrawRectangle(
					 listposition.x,
					 listposition.y,
					 listposition.width,
					 listposition.height,
					bg);
				listposition.width = listposition.width - vtextposx;
				textpos = this->DrawAlignment(listposition, this->list.at(i).text);
				listposition.width = listposition.width+ vtextposx;
				listposition.y = listposition.y + textpos.y+1;
			}
			 
		}
		if (!collision && mousepress) {
			this->toggle = false;

		}

	}

}
#endif










 