#include "sgf/type/mat3x2.h"

namespace sgf::type {
    Mat3x2::Mat3x2():
        m_arrCols{}
    {
    }

    Mat3x2::Mat3x2(
        const Vec2& rCol0,
        const Vec2& rCol1,
        const Vec2& rCol2
    ):
        m_arrCols{
            Vec2(rCol0.x, rCol0.y),
            Vec2(rCol1.x, rCol1.y),
            Vec2(rCol2.x, rCol2.y)
        }
    {
    }

    Mat3x2::Mat3x2(
        float mat[3][2]
    ):
        m_arrCols{
            Vec2(mat[0][0], mat[0][1]),
            Vec2(mat[1][0], mat[1][1]),
            Vec2(mat[2][0], mat[2][1])
        }
    {
    }

    void Mat3x2::plus(
        const Mat3x2& rOther
    ) {
        m_arrCols[0].plus(rOther.m_arrCols[0]);
        m_arrCols[1].plus(rOther.m_arrCols[1]);
        m_arrCols[2].plus(rOther.m_arrCols[2]);
    }

    void Mat3x2::minus(
        const Mat3x2& rOther
    ) {
        m_arrCols[0].minus(rOther.m_arrCols[0]);
        m_arrCols[1].minus(rOther.m_arrCols[1]);
        m_arrCols[2].minus(rOther.m_arrCols[2]);
    }

    void Mat3x2::multiply(
        float fScale
    ) {
        m_arrCols[0].multiply(fScale);
        m_arrCols[1].multiply(fScale);
        m_arrCols[2].multiply(fScale);
    }

    void Mat3x2::divide(
        float fScale
    ) {
        m_arrCols[0].divide(fScale);
        m_arrCols[1].divide(fScale);
        m_arrCols[2].divide(fScale);
    }
}
