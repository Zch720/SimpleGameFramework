#include "sgf/type/mat4x3.h"

namespace sgf::type {
    Mat4x3::Mat4x3():
        m_arrCols{}
    {
    }

    Mat4x3::Mat4x3(
        const Vec3& rCol0,
        const Vec3& rCol1,
        const Vec3& rCol2,
        const Vec3& rCol3
    ):
        m_arrCols{
            Vec3(rCol0.x, rCol0.y, rCol0.z),
            Vec3(rCol1.x, rCol1.y, rCol1.z),
            Vec3(rCol2.x, rCol2.y, rCol2.z),
            Vec3(rCol3.x, rCol3.y, rCol3.z)
        }
    {
    }

    Mat4x3::Mat4x3(
        float mat[4][3]
    ):
        m_arrCols{
            Vec3(mat[0][0], mat[0][1], mat[0][2]),
            Vec3(mat[1][0], mat[1][1], mat[1][2]),
            Vec3(mat[2][0], mat[2][1], mat[2][2]),
            Vec3(mat[3][0], mat[3][1], mat[3][2])
        }
    {
    }

    void Mat4x3::plus(
        const Mat4x3& rOther
    ) {
        m_arrCols[0].plus(rOther.m_arrCols[0]);
        m_arrCols[1].plus(rOther.m_arrCols[1]);
        m_arrCols[2].plus(rOther.m_arrCols[2]);
        m_arrCols[3].plus(rOther.m_arrCols[3]);
    }

    void Mat4x3::minus(
        const Mat4x3& rOther
    ) {
        m_arrCols[0].minus(rOther.m_arrCols[0]);
        m_arrCols[1].minus(rOther.m_arrCols[1]);
        m_arrCols[2].minus(rOther.m_arrCols[2]);
        m_arrCols[3].minus(rOther.m_arrCols[3]);
    }

    void Mat4x3::multiply(
        float fScale
    ) {
        m_arrCols[0].multiply(fScale);
        m_arrCols[1].multiply(fScale);
        m_arrCols[2].multiply(fScale);
        m_arrCols[3].multiply(fScale);
    }

    void Mat4x3::divide(
        float fScale
    ) {
        m_arrCols[0].divide(fScale);
        m_arrCols[1].divide(fScale);
        m_arrCols[2].divide(fScale);
        m_arrCols[3].divide(fScale);
    }
}
