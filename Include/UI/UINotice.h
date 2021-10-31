#pragma once

#include "UIWindow.h"

class CUINotice :
    public CUIWindow
{
    friend class CScene;

private:
    CUINotice();
    virtual ~CUINotice();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void Finsh();
};

