#include "sgf/type/mat2x3.h"

namespace sgf::type {
    Mat2x3::Mat2x3():
        m_arrCols{}
    {
    }

    Mat2x3::Mat2x3(
        const Vec3& rCol0,
        const Vec3& rCol1
    ):
        m_arrCols{
            Vec3(rCol0.x, rCol0.y, rCol0.z),
            Vec3(rCol1.x, rCol1.y, rCol1.z)
        }
    {
    }

    Mat2x3::Mat2x3(
        float mat[2][3]
    ):
        m_arrCols{
            Vec3(mat[0][0], mat[0][1], mat[0][2]),
            Vec3(mat[1][0], mat[1][1], mat[1][2])
        }
    {
    }

    void Mat2x3::plus(
        const Mat2x3& rOther
    ) {
        m_arrCols[0].plus(rOther.m_arrCols[0]);
        m_arrCols[1].plus(rOther.m_arrCols[1]);
    }

    void Mat2x3::minus(
        const Mat2x3& rOther
    ) {
        m_arrCols[0].minus(rOther.m_arrCols[0]);
        m_arrCols[1].minus(rOther.m_arrCols[1]);
    }

    void Mat2x3::multiply(
        float fScale
    ) {
        m_arrCols[0].multiply(fScale);
        m_arrCols[1].multiply(fScale);
    }

    void Mat2x3::divide(
        float fScale
    ) {
        m_arrCols[0].divide(fScale);
        m_arrCols[1].divide(fScale);
    }
}
