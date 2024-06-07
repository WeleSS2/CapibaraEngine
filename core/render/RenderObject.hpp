#include <iostream>

// poxX, posY, width, height
struct cPosSize {
    uint16_t posX;
    uint16_t posY;
    uint16_t width;
    uint16_t height;

    cPosSize() {};
    cPosSize(uint16_t _posX, uint16_t _posY, uint16_t _width, uint16_t _height)
        : posX(_posX), posY(_posY), width(_width), height(_height) {};
};

class cRenderObject{
public:
    cRenderObject() {};

    cRenderObject(const cPosSize& _data) : posSize_(_data) {};

    virtual const void render() const {};

protected:
    cPosSize posSize_;
};