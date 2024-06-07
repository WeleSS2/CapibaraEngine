#include "RenderObject.hpp"
#include <vector>
#include <functional>
#include "raylib.h"

class cButton : private cRenderObject {
public:
    cButton() {};

    cButton (const std::string _id, const cPosSize& data_)
        : id_(_id), cRenderObject(data_) { std::cout << "Cons for id " << _id << std::endl; };

    // Method to add a listener with any number of arguments
    template<typename Func, typename... Args>
    void addListener(Func&& func, Args&&... args) {
        listeners.emplace_back([=]() {
            func(args...);
        });
    }

    // Render color -> texture -> text. It need to looks correctly 
    const void render() const override;

    // DO not use constructor with .set as it's cause double fire of constructor
    const void create(std::string _id, cPosSize data_);

    // Method to trigger listeners
    void click();

    // Check did click is inside
    bool clickCheck(int x, int y) const;

    const std::string& getId() const {return id_; };

    int getY() {return this->posSize_.posY; };

    void applyColor(Color _color);

    void applyText(const std::string& text);

    void applyTexture(const std::string& id);

    void applyTexture(Texture2D* texture_);

protected:
    std::vector<std::function<void()>> listeners;

    bool isClicked_ = false;

    std::string id_ = "DD";

private:
    std::string text_ = "";

    Texture2D* texture_ = nullptr;

    Color color_ = {};

    bool colorApplied = false;

    bool textureApplied = false;

    bool textApplied = false;
};