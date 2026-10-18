#include "sgf/type/mat4.h"

namespace sgf::type {
    Mat4::Mat4():
        m_arrCols{}
    {
    }

    Mat4::Mat4(
        float fScale
    ):
        m_arrCols{
            Vec4(fScale, 0, 0, 0),
            Vec4(0, fScale, 0, 0),
            Vec4(0, 0, fScale, 0),
            Vec4(0, 0, 0, fScale)
        }
    {
    }

    Mat4::Mat4(
        const Vec4& rCol0,
        const Vec4& rCol1,
        const Vec4& rCol2,
        const Vec4& rCol3
    ):
        m_arrCols{
            Vec4(rCol0.x, rCol0.y, rCol0.z, rCol0.w),
            Vec4(rCol1.x, rCol1.y, rCol1.z, rCol1.w),
            Vec4(rCol2.x, rCol2.y, rCol2.z, rCol2.w),
            Vec4(rCol3.x, rCol3.y, rCol3.z, rCol3.w)
        }
    {
    }

    Mat4::Mat4(
        float mat[4][4]
    ):
        m_arrCols{
            Vec4(mat[0][0], mat[0][1], mat[0][2], mat[0][3]),
            Vec4(mat[1][0], mat[1][1], mat[1][2], mat[1][3]),
            Vec4(mat[2][0], mat[2][1], mat[2][2], mat[2][3]),
            Vec4(mat[3][0], mat[3][1], mat[3][2], mat[3][3])
        }
    {
    }

    void Mat4::plus(
        const Mat4& rOther
    ) {
        m_arrCols[0].plus(rOther.m_arrCols[0]);
        m_arrCols[1].plus(rOther.m_arrCols[1]);
        m_arrCols[2].plus(rOther.m_arrCols[2]);
        m_arrCols[3].plus(rOther.m_arrCols[3]);
    }

    void Mat4::minus(
        const Mat4& rOther
    ) {
        m_arrCols[0].minus(rOther.m_arrCols[0]);
        m_arrCols[1].minus(rOther.m_arrCols[1]);
        m_arrCols[2].minus(rOther.m_arrCols[2]);
        m_arrCols[3].minus(rOther.m_arrCols[3]);
    }

    void Mat4::multiply(
        float fScale
    ) {
        m_arrCols[0].multiply(fScale);
        m_arrCols[1].multiply(fScale);
        m_arrCols[2].multiply(fScale);
        m_arrCols[3].multiply(fScale);
    }

    void Mat4::divide(
        float fScale
    ) {
        m_arrCols[0].divide(fScale);
        m_arrCols[1].divide(fScale);
        m_arrCols[2].divide(fScale);
        m_arrCols[3].divide(fScale);
    }
}
