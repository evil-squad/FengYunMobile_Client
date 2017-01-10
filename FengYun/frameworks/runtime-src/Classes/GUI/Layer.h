/**
 * @file  Layer.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef GUI_LAYER_H
#define GUI_LAYER_H

#include "cocos2d.h"
#include "TopLevelNode.h"

namespace gui
{
    class Layer : public cocos2d::Layer
    {
    public:
        static Layer* create();

        //notice: this Layer only accept Window or Panel Child
        virtual void addChild(cocos2d::Node* child) override;
        virtual void addChild(cocos2d::Node* child, int zOrder) override;
        virtual void addChild(cocos2d::Node* child, int zOrder, int tag)override;
        virtual void addChild(cocos2d::Node* child, int zOrder, const std::string& name) override;

        virtual void removeChild(cocos2d::Node* child, bool cleanup) override;

        virtual void closeAll();

    protected:
        virtual bool init() override;

    CC_CONSTRUCTOR_ACCESS:
        Layer();
        virtual ~Layer();

    private:
        CC_DISALLOW_COPY_AND_ASSIGN(Layer);
    };
}

#endif /* GUI_LAYER_H */
