#include "sgf/type/mat3.h"

namespace sgf::type {
    Mat3::Mat3():
        m_arrCols{}
    {
    }

    Mat3::Mat3(
        float fScale
    ):
        m_arrCols{
            Vec3(fScale, 0, 0),
            Vec3(0, fScale, 0),
            Vec3(0, 0, fScale)
        }
    {
    }

    Mat3::Mat3(
        const Vec3& rCol0,
        const Vec3& rCol1,
        const Vec3& rCol2
    ):
        m_arrCols{
            Vec3(rCol0.x, rCol0.y, rCol0.z),
            Vec3(rCol1.x, rCol1.y, rCol1.z),
            Vec3(rCol2.x, rCol2.y, rCol2.z)
        }
    {
    }

    Mat3::Mat3(
        float mat[3][3]
    ):
        m_arrCols{
            Vec3(mat[0][0], mat[0][1], mat[0][2]),
            Vec3(mat[1][0], mat[1][1], mat[1][2]),
            Vec3(mat[2][0], mat[2][1], mat[2][2])
        }
    {
    }

    void Mat3::plus(
        const Mat3& rOther
    ) {
        m_arrCols[0].plus(rOther.m_arrCols[0]);
        m_arrCols[1].plus(rOther.m_arrCols[1]);
        m_arrCols[2].plus(rOther.m_arrCols[2]);
    }

    void Mat3::minus(
        const Mat3& rOther
    ) {
        m_arrCols[0].minus(rOther.m_arrCols[0]);
        m_arrCols[1].minus(rOther.m_arrCols[1]);
        m_arrCols[2].minus(rOther.m_arrCols[2]);
    }

    void Mat3::multiply(
        float fScale
    ) {
        m_arrCols[0].multiply(fScale);
        m_arrCols[1].multiply(fScale);
        m_arrCols[2].multiply(fScale);
    }

    void Mat3::divide(
        float fScale
    ) {
        m_arrCols[0].divide(fScale);
        m_arrCols[1].divide(fScale);
        m_arrCols[2].divide(fScale);
    }
}
