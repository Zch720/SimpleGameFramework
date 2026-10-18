#include "sgf/type/mat4x2.h"

namespace sgf::type {
    Mat4x2::Mat4x2():
        m_arrCols{}
    {
    }

    Mat4x2::Mat4x2(
        const Vec2& rCol0,
        const Vec2& rCol1,
        const Vec2& rCol2,
        const Vec2& rCol3
    ):
        m_arrCols{
            Vec2(rCol0.x, rCol0.y),
            Vec2(rCol1.x, rCol1.y),
            Vec2(rCol2.x, rCol2.y),
            Vec2(rCol3.x, rCol3.y)
        }
    {
    }

    Mat4x2::Mat4x2(
        float mat[4][2]
    ):
        m_arrCols{
            Vec2(mat[0][0], mat[0][1]),
            Vec2(mat[1][0], mat[1][1]),
            Vec2(mat[2][0], mat[2][1]),
            Vec2(mat[3][0], mat[3][1])
        }
    {
    }

    void Mat4x2::plus(
        const Mat4x2& rOther
    ) {
        m_arrCols[0].plus(rOther.m_arrCols[0]);
        m_arrCols[1].plus(rOther.m_arrCols[1]);
        m_arrCols[2].plus(rOther.m_arrCols[2]);
        m_arrCols[3].plus(rOther.m_arrCols[3]);
    }

    void Mat4x2::minus(
        const Mat4x2& rOther
    ) {
        m_arrCols[0].minus(rOther.m_arrCols[0]);
        m_arrCols[1].minus(rOther.m_arrCols[1]);
        m_arrCols[2].minus(rOther.m_arrCols[2]);
        m_arrCols[3].minus(rOther.m_arrCols[3]);
    }

    void Mat4x2::multiply(
        float fScale
    ) {
        m_arrCols[0].multiply(fScale);
        m_arrCols[1].multiply(fScale);
        m_arrCols[2].multiply(fScale);
        m_arrCols[3].multiply(fScale);
    }

    void Mat4x2::divide(
        float fScale
    ) {
        m_arrCols[0].divide(fScale);
        m_arrCols[1].divide(fScale);
        m_arrCols[2].divide(fScale);
        m_arrCols[3].divide(fScale);
    }
}
