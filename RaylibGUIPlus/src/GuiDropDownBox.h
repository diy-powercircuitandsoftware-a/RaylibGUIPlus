#ifndef GUIDropDownBox_H
#define GUIDropDownBox_H

#include "Properties/Alignment.h"
 
#include "GUIComponent.h"
#include <string>
#include <iostream>
#include <vector>
#include "DataUI/ListItem.h"

 
namespace RaylibGUIPlus {
	class GUIDropDownBox : public GUIComponent
{
public:
	 
	GUIDropDownBox(Rectangle rect);
	void  AddListItem(ListItem l);
	Color HoverColor = BLUE;
	RaylibGUIPlus::Alignment TextAlignment = Alignment::Left;
	Color TextColor = BLACK;
	ListItem Value ;
	virtual void AdjustmentSize();
	virtual void Render();
	 
private:
	bool toggle = false;
	std::vector<ListItem> list;
	Vector2 DrawAlignment(Rectangle rect,std::string s);
	void DrawNormalMode (Vector2 pos,bool mousepress, Vector2 mousepoint, int vtextposx);
};
	 
	 
	GUIDropDownBox::GUIDropDownBox(Rectangle rect)
	{
		this->Rect = rect;
	}
	void GUIDropDownBox::AddListItem(ListItem l) {  
		this->list.push_back(l);
		this->Value = l;
	}
	void GUIDropDownBox::AdjustmentSize() {
		this->Rect.height = this->Font.baseSize ;
	}
	Vector2 GUIDropDownBox::DrawAlignment(Rectangle rect, std::string s ) {
		  
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
	void GUIDropDownBox::DrawNormalMode(Vector2 pos,bool mousepress,Vector2 mousepoint,int vtextposx) {
 
		
		Rectangle listposition = this->Rect;
		listposition.y = listposition.y + pos.y;
		listposition.width = listposition.width + vtextposx;
		DrawRectangle(
			listposition.x - this->BorderSize,
			listposition.y - this->BorderSize,
			listposition.width + (this->BorderSize * 2),
			(listposition.height * this->list.size()) + ((this->BorderSize + 1) * 2),
			this->BorderColor);
		for (int i = 0; i < this->list.size(); i++) {
			bool listcollision = CheckCollisionPointRec(mousepoint, listposition);
			Color bg = this->BackgroundColor;
			if (listcollision) {
				bg = this->HoverColor;
			}
			if (listcollision && mousepress) {
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
			pos = this->DrawAlignment(listposition, this->list.at(i).text);
			listposition.width = listposition.width + vtextposx;
			listposition.y = listposition.y + pos.y + 1;
		}
		 
	}
	void GUIDropDownBox::Render()
	{
		this->Event.Reset();
		int vtextposx = MeasureTextEx(this->Font, "V", this->Font.baseSize, 0).x*1.2;

		DrawRectangle(
			this->Rect.x- this->BorderSize,
			this->Rect.y- this->BorderSize,
			this->Rect.width+ vtextposx + (this->BorderSize*2),
			this->Rect.height+ (this->BorderSize*2),
			this->BorderColor);
			
		DrawTextEx(this->Font,
			"V",
			(Vector2){
			this->Rect.x+ this->Rect.width+ (this->BorderSize * 2),
				this->Rect.y
			}, this->Font.baseSize, 0, this->BackgroundColor);
		 
		DrawRectangle(
			this->Rect.x,
			this->Rect.y,
			this->Rect.width,
			this->Rect.height,
			this->BackgroundColor);
			Vector2 mousepoint = GetMousePosition();
			this->Rect.width = this->Rect.width + vtextposx;
			bool collision = CheckCollisionPointRec(mousepoint, this->Rect);
			bool mousepress = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
			this->Rect.width = this->Rect.width - vtextposx;
		if (collision && mousepress&& this->Enable) {
			this->toggle = !this->toggle;
		}else if (collision && mousepress && !this->Enable) {
			this->toggle = false;
		}
		this->Event.MouseDown = collision && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
		Vector2 textpos = this->DrawAlignment(this->Rect, this->Value.text);

		if (this->toggle) {
		 	this->DrawNormalMode(textpos, mousepress,  mousepoint,  vtextposx);
			 
		}
		if (!collision && mousepress) {
			this->toggle = false;

		}

	}

}
#endif










 