/**
 * @file  GameModule.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef GAMEMODULE_H
#define GAMEMODULE_H

#include "gamebase.h"
#include <type_traits>

BEGIN_NS_FY

class GameConfigLoader;
class GameModule;

template <class T>
class GameModuleKey
{
public:
    typedef T module_type;
    static_assert(std::is_base_of<GameModule, T>::value, "Module Type must devied from GameModuel");
};

class GameModule
{
public:
    virtual ~GameModule() {}

    virtual void onLoadConfig(GameConfigLoader* loader) {}
    virtual void onInitialize() {}
    virtual void onRelease() {}

    template <class T>
    static T* get() { return get(GameModuleKey<T>()); }

    template <class K>
    static typename K::module_type* get(K)
    {
        return Holder<K>::module_instance;
    }

    template <class T>
    static void set(T* module) { set(GameModuleKey<T>(), module); }

    template <class K>
    static void set(K, typename K::module_type* module)
    {
        Holder<K>::module_instance = module;
    }

private:
    template <class K>
    struct Holder
    {
        static typename K::module_type* module_instance;
    };
};

template <class K>
typename K::module_type *GameModule::Holder<K>::module_instance = nullptr;

END_NS_FY
#endif /* GAMEMODULE_H */
