#pragma once

#include <iostream>
#include <vector>
#include <map>
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
    void addListener(cID id, Func&& func, Args&&... args) 
    {
        std::cout << "Listener added" << std::endl;
        listeners_.emplace_back(std::make_pair(id, 
                [=]() {
                    func(args...);
                }));
    }

    // Method to trigger listeners
    void click();

    /*
     * Advanced method to trigger listeners but only selected
     */
    void executeListeners(const cID& id);

    // Check did mouse is inside
    bool mouseCheck(int x, int y) const;

protected:
    std::vector<std::pair<cID, std::function<void()>>> listeners_;

    bool isClicked_ = false;

private:
    std::shared_ptr<cPositionObject> data_ = nullptr;
};