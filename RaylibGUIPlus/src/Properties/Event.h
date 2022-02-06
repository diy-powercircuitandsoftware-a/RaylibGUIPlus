#ifndef Event_H
#define Event_H
namespace RaylibGUIPlus {
    typedef struct Event {
        bool MouseDown = false;
        bool KeyDown = false;
        void Reset() {
            MouseDown = false;
            KeyDown = false;
        }
    } Event;
}
#endif
