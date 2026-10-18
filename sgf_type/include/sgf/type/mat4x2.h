#pragma once

#include <stdint.h>

#include "sgf/type/vec2.h"

namespace sgf::type {
    class Mat4x2 {
    public:
        Mat4x2();
        Mat4x2(
            const Vec2& rCol0,
            const Vec2& rCol1,
            const Vec2& rCol2,
            const Vec2& rCol3
        );
        Mat4x2(float mat[4][2]);

        inline Vec2& operator[](
            uint32_t nIndex
        ) {
            return m_arrCols[nIndex];
        }

        inline const Vec2& operator[](
            uint32_t nIndex
        ) const {
            return m_arrCols[nIndex];
        }

        void plus(const Mat4x2& rOther);
        void minus(const Mat4x2& rOther);
        void multiply(float fScale);
        void divide(float fScale);

        inline bool equal(
            const Mat4x2& rOther
        ) const {
            return m_arrCols[0].equal(rOther.m_arrCols[0]) && m_arrCols[1].equal(rOther.m_arrCols[1]) && m_arrCols[2].equal(rOther.m_arrCols[2]) && m_arrCols[3].equal(rOther.m_arrCols[3]);
        }

    private:
        Vec2 m_arrCols[4];
    };
}
