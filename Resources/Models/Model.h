#pragma once
#include "Mesh.h"

class CModel
{
protected:
    CModel(const CModel& ) = delete;
    unsigned int m_Id = 0;
    static unsigned int s_Id;
};
