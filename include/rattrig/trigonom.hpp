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

}  // namespace rattrig