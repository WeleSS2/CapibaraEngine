#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include "structs.h"
#include "positionObject.h"

class cClickObject
{
public:
    cClickObject(cPositionObject _data);

    cClickObject(std::shared_ptr<cPositionObject> _data);

    virtual ~cClickObject() { };
    
    void setPositionObject(std::shared_ptr<cPositionObject> _data);

    std::shared_ptr<cPositionObject> getPositionObject() const;

    /*
     * Custom listeners for buttons 
     */
    template<typename Func, typename... Args>
    void addListener(Func&& func, Args&&... args) 
    {
        std::cout << "Listener added" << std::endl;
        listeners_.emplace_back([=]() {
            func(args...);
        });
    }

    // Method to trigger listeners
    void click();

    // Check did click is inside
    bool clickCheck(int x, int y) const;

protected:
    std::vector<std::function<void()>> listeners_;

    bool isClicked_ = false;

private:
    std::shared_ptr<cPositionObject> data_ = nullptr;
};