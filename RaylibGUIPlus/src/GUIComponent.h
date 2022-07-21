#ifndef GUIComponent_H
#define GUIComponent_H
#include "raylib.h"
#include "Properties/Event.h"
namespace RaylibGUIPlus {
	class GUIComponent {

	public:
		  GUIComponent();
		  ~GUIComponent();
		void AdjustmentSize();

		Color BackgroundColor = RAYWHITE;
		Color BorderColor = BLACK;
		int BorderSize = 1;
		bool Enable = true;
		Event Event;
		Font Font = GetFontDefault();
		Vector2 Position;
		Rectangle Rect;
		void Render();
		Color TextColor = BLACK;
	private:

	};
	void GUIComponent::AdjustmentSize() {
		 
	}
	GUIComponent::GUIComponent() {
	 
	}
	GUIComponent::~GUIComponent() {
		UnloadFont(this->Font);
	}
	void GUIComponent::Render() {

	}
}
#endif