//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef GRBL_VEC3_H
#define GRBL_VEC3_H

#include <cmath>
#include <cfloat>

struct vec3 {
    float v[3];

    inline float x() const {
        return v[0];
    }

    inline float y() const {
        return v[1];
    }

    inline float z() const {
        return v[2];
    }

    explicit vec3();

    explicit vec3(float x, float y, float z);

    inline vec3 &operator+=(const vec3 &vector) {
        v[0] += vector.v[0];
        v[1] += vector.v[1];
        v[2] += vector.v[2];
        return *this;
    }

    inline vec3 &operator-=(const vec3 &vector) {
        v[0] -= vector.v[0];
        v[1] -= vector.v[1];
        v[2] -= vector.v[2];
        return *this;
    }

    inline friend vec3 operator+(const vec3 &v1, const vec3 &v2) {
        return vec3(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2]);
    }

    friend inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
        return vec3(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]);
    }

    friend inline bool operator==(const vec3 &v1, const vec3 &v2) {
        bool c1 = fabs(v1.v[0] - v2.v[0]) <= FLT_EPSILON;
        bool c2 = fabs(v1.v[1] - v2.v[1]) <= FLT_EPSILON;
        bool c3 = fabs(v1.v[2] - v2.v[2]) <= FLT_EPSILON;

        return c1 && c2 && c3;
    }
};

#endif //GRBL_VEC3_H
