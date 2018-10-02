#pragma once

#include <array>

namespace Core
{
	class Point3
	{
	public:
		constexpr Point3()
			: x_(0.0)
			, y_(0.0)
			, z_(0.0) {
		}

		constexpr Point3(double x, double y, double z)
			: x_(x)
			, y_(y)
			, z_(z) {
		}

		double x() const;
		void setX(double value);

		double y() const;
		void setY(double value);

		double z() const;
		void setZ(double value);

		/**
		 * @brief Вычисляет расстояние от текущей до целевой точки.
		 */
		double distanceToPoint(const Point3 &target);

		/**
		 * @brief Проверяет на нулевое состояние ветора.
		 * @return true - если все координаты равны нулю, false - в противном случае
		 */
		bool isNull() const;

		/**
		 * @brief Возврвщает расстояние от начала координат до текущей точки.
		 */
		double length() const;

		std::array<double, 3> values() const;

		Point3 &operator+=(const Point3 &other);
		Point3 &operator-=(const Point3 &other);

		constexpr friend bool operator==(const Point3 &lhs, const Point3 &rhs) {
			return (lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_ && lhs.z_ == rhs.z_);
		}

		constexpr friend bool operator!=(const Point3 &lhs, const Point3 &rhs) {
			return !(lhs == rhs);
		}

		constexpr friend const Point3 operator+(const Point3 &lhs, const Point3 &rhs) {
			return Point3(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_);
		}

		constexpr friend const Point3 operator-(const Point3 &lhs, const Point3 &rhs) {
			return Point3(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_);
		}

	private:
		double x_;
		double y_;
		double z_;
	};
}
