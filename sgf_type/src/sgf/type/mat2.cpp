#include "sgf/type/mat2.h"

namespace sgf::type {
    Mat2::Mat2():
        m_arrCols{}
    {
    }

    Mat2::Mat2(
        float fScale
    ):
        m_arrCols{
            Vec2(fScale, 0),
            Vec2(0, fScale)
        }
    {
    }

    Mat2::Mat2(
        const Vec2& rCol0,
        const Vec2& rCol1
    ):
        m_arrCols{
            Vec2(rCol0.x, rCol0.y),
            Vec2(rCol1.x, rCol1.y)
        }
    {
    }

    Mat2::Mat2(
        float mat[2][2]
    ):
        m_arrCols{
            Vec2(mat[0][0], mat[0][1]),
            Vec2(mat[1][0], mat[1][1])
        }
    {
    }

    void Mat2::plus(
        const Mat2& rOther
    ) {
        m_arrCols[0].plus(rOther.m_arrCols[0]);
        m_arrCols[1].plus(rOther.m_arrCols[1]);
    }

    void Mat2::minus(
        const Mat2& rOther
    ) {
        m_arrCols[0].minus(rOther.m_arrCols[0]);
        m_arrCols[1].minus(rOther.m_arrCols[1]);
    }

    void Mat2::multiply(
        float fScale
    ) {
        m_arrCols[0].multiply(fScale);
        m_arrCols[1].multiply(fScale);
    }

    void Mat2::divide(
        float fScale
    ) {
        m_arrCols[0].divide(fScale);
        m_arrCols[1].divide(fScale);
    }
}
