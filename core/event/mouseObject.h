#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "structs.h"
#include "positionObject.h"

/*
 * Base class for all interactive objects.
 * It have listeners which wait where you can specify ID
 * of the action and add this action in main loop.
 * TODO: Main loop where you can push type of action
 *   cMouseObject(cPositionObject _data) {};
 *   cMouseObject(std::shared_ptr<cPositionObject> _data) {};
 */
class cMouseObject
{
public:
    cMouseObject(cPositionObject _data);

    cMouseObject(std::shared_ptr<cPositionObject> _data);

    virtual ~cMouseObject() { };
    
    void setPositionObject(std::shared_ptr<cPositionObject> _data);

    /*
     * Get position
     */
    std::shared_ptr<cPositionObject> getPositionObject() const;

    /*
     * Custom listeners for buttons 
     */
    template<typename Func, typename... Args>
    void addListener(cID id, Func&& func, Args&&... args) 
    {
        listeners_.emplace_back(std::make_pair(id, 
                [=]() {
                    func(args...);
                }));
    }

    /*
     * Advanced method to trigger listeners but only selected
     */
    void executeListeners(const cID& id);

    /*
     * Check if mouse is inside
     */
    bool mouseCheck(int x, int y) const;

protected:
    std::vector<std::pair<cID, std::function<void()>>> listeners_;

private:
    std::shared_ptr<cPositionObject> data_ = nullptr;
};