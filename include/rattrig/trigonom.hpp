#pragma once

/** @file include/trigonom.hpp
 *  This is a C++ Library header.
 *
 * Rational Trigonometry is a new approach to classical trigonometry, developed by
 * Norman Wildberger, that aims to simplify and clarify the subject by using only
 * rational numbers and operations, rather than irrational numbers and limits.
 *
 * In traditional trigonometry, concepts such as the sine, cosine, and tangent of
 * an angle are typically defined using circles and the unit circle in particular.
 * These definitions involve irrational numbers and limits, which can make the
 * subject more difficult to understand and work with.
 *
 * In rational trigonometry, Wildberger replaces these circular definitions with
 * ones based on lines and line segments, which allows for a more straightforward
 * and intuitive approach. The fundamental concepts in rational trigonometry are
 * the "quadaverage" and the "dilated directed angle," which are defined in terms
 * of lines and line segments, rather than circles.
 *
 * Rational trigonometry has been gaining popularity in recent years, as it
 * provides a useful alternative to traditional trigonometry for certain
 * applications, such as computer graphics, robotics, and physics. It can also be a
 * helpful tool for students who struggle with the irrational numbers and limits
 * used in traditional trigonometry.
 *
 * In summary, Rational Trigonometry is a new approach to classical trigonometry
 * that uses rational numbers and operations, rather than irrational numbers and
 * limits, making it a more straightforward and intuitive subject to understand and
 * work with.
 */

#include <vector>

namespace rattrig {

    /**
     * @brief Calculates the quadrea of a triangle using Archimedes' formula.
     *
     * Takes the lengths of the triangle's three sides as parameters q1, q2, q3.
     * Returns the quadrea calculation result.
     *
     * Can also be used to check if a quadraple of lengths Q1, Q2, Q3, Q4 is on a
     * circle.
     *
     * @param[in] q_1 Represents the length of the first side of the triangle.
     * @param[in] q_2 Represents the length of the second side of the triangle.
     * @param[in] q_3 The parameter `q_3` represents the length of the third side of
     * the triangle.
     *
     * @return The function `archimedes` returns the area of a triangle computed
     * using Archimedes' formula, given the lengths of the 3 sides.
     *
     */
    template <typename T> constexpr T archimedes(const T &q_1, const T &q_2, const T &q_3) {
        T temp = q_1 + q_2 - q_3;
        return 4 * q_1 * q_2 - temp * temp;
    }

    /**
     * @brief Calculates the cross product of two 2D vectors.
     *
     * @param v_1 First vector as std::vector<T> of size 2
     * @param v_2 Second vector as std::vector<T> of size 2
     * @return Cross product of the two vectors
     */
    template <typename T> constexpr T cross(const std::vector<T> &v_1, const std::vector<T> &v_2) {
        return v_1[0] * v_2[1] - v_1[1] * v_2[0];
    }

    /**
     * @brief Calculates the dot product of two 2D vectors.
     *
     * @param v_1 First vector as std::vector<T> of size 2
     * @param v_2 Second vector as std::vector<T> of size 2
     * @return Dot product of the two vectors
     */
    template <typename T> constexpr T dot(const std::vector<T> &v_1, const std::vector<T> &v_2) {
        return v_1[0] * v_2[0] + v_1[1] * v_2[1];
    }

    /**
     * @brief Calculates the quadrance (squared length) of a 2D vector.
     *
     * @param vec Vector as std::vector<T> of size 2
     * @return Quadrance of the vector
     */
    template <typename T> constexpr T quad(const std::vector<T> &vec) {
        return vec[0] * vec[0] + vec[1] * vec[1];
    }

    /**
     * @brief Calculates the spread between two 2D vectors.
     *
     * The spread is defined as the square of the cross product divided by
     * the product of the quadrances of the two vectors.
     *
     * @param v_1 First vector as std::vector<T> of size 2
     * @param v_2 Second vector as std::vector<T> of size 2
     * @return Spread between the two vectors
     */
    template <typename T> constexpr T spread(const std::vector<T> &v_1, const std::vector<T> &v_2) {
        T cross_val = cross(v_1, v_2);
        return (cross_val * cross_val) / (quad(v_1) * quad(v_2));
    }

    /**
     * @brief Calculates the third quadrance using the triple quad formula.
     *
     * Given two quadrances and the spread between them, calculates the third quadrance.
     *
     * @param q_1 First quadrance
     * @param q_2 Second quadrance
     * @param spr_val Spread between the two vectors
     * @return Third quadrance
     */
    template <typename T>
    constexpr T triple_quad_formula(const T &q_1, const T &q_2, const T &spr_val) {
        T sum = q_1 + q_2;
        return sum * sum - 4 * q_1 * q_2 * (1 - spr_val);
    }

    /**
     * @brief Calculates the spread using the spread law.
     *
     * Given three quadrances of a triangle, calculates the spread.
     *
     * @param q_1 First quadrance
     * @param q_2 Second quadrance
     * @param q_3 Third quadrance
     * @return Spread
     */
    template <typename T> constexpr T spread_law(const T &q_1, const T &q_2, const T &q_3) {
        T numerator = q_1 + q_2 - q_3;
        return 1 - (numerator * numerator) / (4 * q_1 * q_2);
    }
}  // namespace rattrig
