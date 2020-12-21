//
// Created by Lado on 11/6/20.
//

#ifndef LOTOS_ENTITYCOMPONENT_H
#define LOTOS_ENTITYCOMPONENT_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "SDL.h"

class Component;
class Entity;
class Manage;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template<typename T> inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
    Entity *entity;
    virtual void init() {  }
    virtual void update() {  }
    virtual void draw() {  }
    virtual ~Component() {  }
};

class Entity {
private:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;
    Manage& manager;
    bool pressed = false;

public:
    Entity(Manage& manager1) : manager(manager1) {  }

    void update() {
        for (auto& c: components) c -> update();
    }
    void draw() {
        for (auto& c: components) c -> draw();
    }
    bool isActive() const { return active; }
    void destroy() { active = false; }

    bool hasGroup(Group mGroup) {
        return groupBitSet[mGroup];
    }

    void addGroup(Group mGroup);
    void delGroup(Group mGroup) {
        groupBitSet[mGroup] = false;
    }

    template<typename T> bool hasComponent() const {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template<typename T, typename... TArgs> T& addComponents(TArgs&&... mArgs) {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T> T& getComponent() const {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    void init_event(SDL_MouseButtonEvent *event) {
        if(event->button == SDL_BUTTON_LEFT) {
            pressed = true;
            std::cout << "Pressed" << std::endl;
        }
    }
};

class Manage {
private:
    std::vector<std::unique_ptr<Entity>> entites;
    std::array<std::vector<Entity*>, maxGroups> groupedEntites;

public:
    void update() {
        for(auto& e : entites) e->update();
    }
    void draw() {
        for(auto& e : entites) e->draw();
    }
    void refresh() {
        for(auto i (0u); i < maxGroups; i++) {
            auto& v(groupedEntites[i]);
            v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity) {
                return !mEntity->isActive() || !mEntity->hasGroup(i);
            }), std::end(v));
        }

        entites.erase(std::remove_if(std::begin(entites), std::end(entites), [](const std::unique_ptr<Entity>&mEntity) {
            return !mEntity->isActive();
        }), std::end(entites));
    }

    void addToGroup(Entity* mEntity, Group mGroup) {
        groupedEntites[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& getGroup(Group mGroup) {
        return groupedEntites[mGroup];
    }

    Entity& addEntity() {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr { e };
        entites.emplace_back(std::move(uPtr));
        return *e;
    }
};

#endif //LOTOS_ENTITYCOMPONENT_H
