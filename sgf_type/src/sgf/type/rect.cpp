#include "sgf/type/rect.h"

namespace sgf {
    Rect::Rect():
        width(0),
        height(0)
    {
    }
    
    Rect::Rect(float width, float height):
        width(width),
        height(height)
    {
    }
}
