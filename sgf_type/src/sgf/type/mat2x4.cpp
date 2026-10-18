#include "sgf/type/mat2x4.h"

namespace sgf::type {
    Mat2x4::Mat2x4():
        m_arrCols{}
    {
    }

    Mat2x4::Mat2x4(
        const Vec4& rCol0,
        const Vec4& rCol1
    ):
        m_arrCols{
            Vec4(rCol0.x, rCol0.y, rCol0.z, rCol0.w),
            Vec4(rCol1.x, rCol1.y, rCol1.z, rCol1.w)
        }
    {
    }

    Mat2x4::Mat2x4(
        float mat[2][4]
    ):
        m_arrCols{
            Vec4(mat[0][0], mat[0][1], mat[0][2], mat[0][3]),
            Vec4(mat[1][0], mat[1][1], mat[1][2], mat[1][3])
        }
    {
    }

    void Mat2x4::plus(
        const Mat2x4& rOther
    ) {
        m_arrCols[0].plus(rOther.m_arrCols[0]);
        m_arrCols[1].plus(rOther.m_arrCols[1]);
    }

    void Mat2x4::minus(
        const Mat2x4& rOther
    ) {
        m_arrCols[0].minus(rOther.m_arrCols[0]);
        m_arrCols[1].minus(rOther.m_arrCols[1]);
    }

    void Mat2x4::multiply(
        float fScale
    ) {
        m_arrCols[0].multiply(fScale);
        m_arrCols[1].multiply(fScale);
    }

    void Mat2x4::divide(
        float fScale
    ) {
        m_arrCols[0].divide(fScale);
        m_arrCols[1].divide(fScale);
    }
}
