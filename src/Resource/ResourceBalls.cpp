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

void ResourceBalls::append(ResourceBall *resourceBall){
    resourceBalls.push_front(resourceBall);
}