#include "RenderObject.hpp"

class cTexture : private cRenderObject {
public:
    cTexture (const std::string &_id, const std::string& path, const cPosSize& data_)
        : id_(_id), cRenderObject(data_) {};

    const void render() const override;

    const void loadTexture(const std::string& path) const;

    const Texture2D* getTexture() const { return &texture; };

    const std::string getTextureId() const { return id_; };
protected:
    std::string id_;

    Texture2D texture;
};