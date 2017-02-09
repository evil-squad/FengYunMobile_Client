/**
 * @file  RoleData.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/8.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ROLEDATA_H
#define ROLEDATA_H

#include <string>
#include <vector>
#include <deque>
#include <map>

#include "RoleTypes.h"
#include "MathTypes.h"
#include "gamebase.h"

BEGIN_NS_FY

class RoleNavData
{
public:
    enum class SourceType
    {
        NONE = 0,
        TASK
    };

    enum class TargetType
    {
        NONE = 0,
        NPC,
        GATE,
        COLLECT_ITEM,
        TREASURE,
        POS
    };

    struct Source
    {
        SourceType type;
        int id;
    };

    struct Target
    {
        TargetType type;
        int id;
        Vector3 pos;
    };

    const Source& getSource() const { return _source; }
    void setSource(const Source& source) { _source = source; }

    bool hasNextTarget() const { return getNextTarget() != nullptr; }

    const Target* getNextTarget() const
    {
        if (_targets.empty()) return nullptr;
        return &_targets.front();
    }

    void setTargets(const std::vector<Target>& targets)
    {
        _targets.clear();
        _targets.assign(targets.begin(), targets.end());
    }

    void removeNextTarget()
    {
        _targets.pop_front();
    }

    void clearTargets()
    {
        _targets.clear();
    }

private:
    Source _source;
    std::deque<Target> _targets;
};

class RoleData
{
public:
    RoleData()
    : _navData()
    {}

    ~RoleData()
    {}

    const RoleNavData& getNavData() const { return _navData; }
    RoleNavData& getNavData() { return _navData; }

    bool isNavigating() const
    {
        return getNavData().hasNextTarget();
    }
private:
    RoleNavData _navData;
};

END_NS_FY
#endif /* ROLEDATA_H */
