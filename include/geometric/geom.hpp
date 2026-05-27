#pragma once

namespace geom {

    struct Vec3 {
        double x;
        double y;
        double z;

        Vec3() = default;

        Vec3(double x_, double y_, double z_)
            : x(x_), y(y_), z(z_) {
        }

        Vec3 operator+(const Vec3& other) const {
            return Vec3{ x + other.x, y + other.y, z + other.z };
        }

        Vec3 operator-(const Vec3& other) const {
            return Vec3{ x - other.x, y - other.y, z - other.z };
        }

        Vec3 operator*(double scalar) const {
            return Vec3{ x * scalar, y * scalar, z * scalar };
        }

        double dot(const Vec3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }
    };

    inline Vec3 operator*(double scalar, const Vec3& v) {
        return v * scalar;
    }

}