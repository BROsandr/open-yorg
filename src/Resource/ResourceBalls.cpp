#include "Resource/ResourceBalls.hpp"
#include "Resource/ResourceBall.hpp"

void ResourceBalls::tick(){
    for (auto &el : resourceBalls) {
        if (el->deleted) {
            delete el;
            el = nullptr;
            continue;
        }
        el->update();
        el->draw();
    }

    resourceBalls.remove(nullptr);
}

bool ResourceBalls::isResourceNearby(const FieldCell &fieldCell){
    // if(fieldCell at left contains resourceType == this::type){
    //     return true
    // }
    return true;
}

void ResourceBalls::append(ResourceBall *resourceBall){
    resourceBalls.push_front(resourceBall);
}