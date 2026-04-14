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

#include <limits>
#include <stdexcept>
#include <vector>

/// @brief Rational Trigonometry library namespace.
///
/// This namespace contains functions implementing rational trigonometry,
/// an alternative approach to classical trigonometry based on rational
/// numbers and geometric concepts like quadrance and spread instead of
/// angles and trigonometric functions.
namespace rattrig {

/// @brief Exception class for rational trigonometry errors
class TrigonomError : public std::runtime_error {
public:
    explicit TrigonomError(const std::string& message) : std::runtime_error(message) {}
};

/// @brief Validates that a vector has the expected size
/// @tparam T Type of vector elements
/// @param vec Vector to validate
/// @param expected_size Expected vector size
/// @throws TrigonomError if vector size doesn't match
template <typename T>
constexpr void validate_vector_size(const std::vector<T>& vec, size_t expected_size) {
    if (vec.size() != expected_size) {
        throw TrigonomError("Vector must have exactly " + std::to_string(expected_size) +
                            " elements, got " + std::to_string(vec.size()));
    }
}

/// @brief Validates that a value is non-zero (for division operations)
/// @tparam T Type of value
/// @param value Value to validate
/// @param param_name Name of parameter for error message
/// @throws TrigonomError if value is zero
template <typename T>
constexpr void validate_non_zero(const T& value, const std::string& param_name) {
    if (value == T(0)) {
        throw TrigonomError("Parameter '" + param_name + "' cannot be zero");
    }
}

/// @brief Validates that a value is non-negative
/// @tparam T Type of value
/// @param value Value to validate
/// @param param_name Name of parameter for error message
/// @throws TrigonomError if value is negative
template <typename T>
constexpr void validate_non_negative(const T& value, const std::string& param_name) {
    if (value < T(0)) {
        throw TrigonomError("Parameter '" + param_name + "' cannot be negative");
    }
}

/// @brief Validates that a multiplication won't overflow
/// @tparam T Type of values
/// @param a First value
/// @param b Second value
/// @param param_name Name of parameter for error message
/// @throws TrigonomError if multiplication would overflow
template <typename T>
constexpr void validate_no_overflow_multiply(const T& a, const T& b, const std::string& param_name) {
    if constexpr (std::is_integral_v<T>) {
        if (a != 0 && b != 0) {
            if ((a > 0 && b > 0 && a > std::numeric_limits<T>::max() / b) ||
                (a < 0 && b < 0 && a < std::numeric_limits<T>::max() / b) ||
                (a > 0 && b < 0 && b < std::numeric_limits<T>::min() / a) ||
                (a < 0 && b > 0 && a < std::numeric_limits<T>::min() / b)) {
                throw TrigonomError("Multiplication overflow for parameter '" + param_name + "'");
            }
        }
    }
}

/// @brief Validates that an addition won't overflow
/// @tparam T Type of values
/// @param a First value
/// @param b Second value
/// @param param_name Name of parameter for error message
/// @throws TrigonomError if addition would overflow
template <typename T>
constexpr void validate_no_overflow_add(const T& a, const T& b, const std::string& param_name) {
    if constexpr (std::is_integral_v<T>) {
        if (a > 0 && b > 0 && a > std::numeric_limits<T>::max() - b) {
            throw TrigonomError("Addition overflow for parameter '" + param_name + "'");
        }
        if (a < 0 && b < 0 && a < std::numeric_limits<T>::min() - b) {
            throw TrigonomError("Addition underflow for parameter '" + param_name + "'");
        }
    }
}

/// @brief Validates that a square operation won't overflow
/// @tparam T Type of value
/// @param a Value to square
/// @param param_name Name of parameter for error message
/// @throws TrigonomError if squaring would overflow
template <typename T>
constexpr void validate_no_overflow_square(const T& a, const std::string& param_name) {
    if constexpr (std::is_integral_v<T>) {
        if (a != 0) {
            T abs_a = (a < 0) ? -a : a;
            if (abs_a > std::numeric_limits<T>::max() / abs_a) {
                throw TrigonomError("Square overflow for parameter '" + param_name + "'");
            }
        }
    }
}

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
        validate_no_overflow_multiply(q_1, q_2, "q_1 in archimedes");
        validate_no_overflow_multiply(q_1, T(4), "4 * q_1 in archimedes");
        validate_no_overflow_multiply(q_2, T(4), "4 * q_2 in archimedes");
        
        T temp = q_1 + q_2 - q_3;
        validate_no_overflow_square(temp, "temp in archimedes");
        
        return 4 * q_1 * q_2 - temp * temp;
    }

    // ========== 2D Vector Operations ==========

    /**
     * @brief Calculates the cross product of two 2D vectors.
     *
     * @param v_1 First vector as std::vector<T> of size 2
     * @param v_2 Second vector as std::vector<T> of size 2
     * @return Cross product of the two vectors
     * @throws TrigonomError if vectors don't have size 2 or overflow occurs
     */
    template <typename T> constexpr T cross(const std::vector<T> &v_1, const std::vector<T> &v_2) {
        validate_vector_size(v_1, 2);
        validate_vector_size(v_2, 2);
        validate_no_overflow_multiply(v_1[0], v_2[1], "v_1[0] * v_2[1] in cross");
        validate_no_overflow_multiply(v_1[1], v_2[0], "v_1[1] * v_2[0] in cross");
        return v_1[0] * v_2[1] - v_1[1] * v_2[0];
    }

    /**
     * @brief Calculates the dot product of two 2D vectors.
     *
     * @param v_1 First vector as std::vector<T> of size 2
     * @param v_2 Second vector as std::vector<T> of size 2
     * @return Dot product of the two vectors
     * @throws TrigonomError if vectors don't have size 2 or overflow occurs
     */
    template <typename T> constexpr T dot(const std::vector<T> &v_1, const std::vector<T> &v_2) {
        validate_vector_size(v_1, 2);
        validate_vector_size(v_2, 2);
        validate_no_overflow_multiply(v_1[0], v_2[0], "v_1[0] * v_2[0] in dot");
        validate_no_overflow_multiply(v_1[1], v_2[1], "v_1[1] * v_2[1] in dot");
        return v_1[0] * v_2[0] + v_1[1] * v_2[1];
    }

    /**
     * @brief Calculates the quadrance (squared length) of a 2D vector.
     *
     * @param vec Vector as std::vector<T> of size 2
     * @return Quadrance of the vector
     * @throws TrigonomError if vector doesn't have size 2 or overflow occurs
     */
    template <typename T> constexpr T quad(const std::vector<T> &vec) {
        validate_vector_size(vec, 2);
        validate_no_overflow_square(vec[0], "vec[0] in quad");
        validate_no_overflow_square(vec[1], "vec[1] in quad");
        validate_no_overflow_add(vec[0] * vec[0], vec[1] * vec[1], "quad sum");
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
     * @throws TrigonomError if vectors don't have size 2, have zero length, or overflow occurs
     */
    template <typename T> constexpr T spread(const std::vector<T> &v_1, const std::vector<T> &v_2) {
        validate_vector_size(v_1, 2);
        validate_vector_size(v_2, 2);
        
        T q1 = quad(v_1);
        T q2 = quad(v_2);
        
        validate_non_zero(q1, "quad(v_1)");
        validate_non_zero(q2, "quad(v_2)");
        validate_no_overflow_multiply(q1, q2, "q1 * q2 in spread");
        
        T cross_val = cross(v_1, v_2);
        validate_no_overflow_square(cross_val, "cross_val in spread");
        return (cross_val * cross_val) / (q1 * q2);
    }

    /**
     * @brief Calculates the third quadrance using the triple quad formula.
     *
     * Given two quadrances and the spread between them, calculates the third quadrance.
     *
     * @param q_1 First quadrance
     * @param q_2 Second quadrance
     * @param spr_val Spread between the two vectors
     * @return Third quadrance (squared value)
     * @throws TrigonomError if overflow occurs
     */
    template <typename T>
    constexpr T triple_quad_formula(const T &q_1, const T &q_2, const T &spr_val) {
        validate_no_overflow_add(q_1, q_2, "q_1 + q_2 in triple_quad_formula");
        validate_no_overflow_multiply(q_1, q_2, "q_1 * q_2 in triple_quad_formula");
        validate_no_overflow_multiply(q_1 * q_2, T(4), "4 * q_1 * q_2 in triple_quad_formula");
        
        T sum = q_1 + q_2;
        validate_no_overflow_square(sum, "sum in triple_quad_formula");
        
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
     * @throws TrigonomError if q_1 or q_2 is zero or overflow occurs
     */
    template <typename T> constexpr T spread_law(const T &q_1, const T &q_2, const T &q_3) {
        validate_non_zero(q_1, "q_1");
        validate_non_zero(q_2, "q_2");
        validate_no_overflow_multiply(q_1, q_2, "q_1 * q_2 in spread_law");
        validate_no_overflow_multiply(q_1 * q_2, T(4), "4 * q_1 * q_2 in spread_law");
        
        T numerator = q_1 + q_2 - q_3;
        validate_no_overflow_square(numerator, "numerator in spread_law");
        
        return 1 - (numerator * numerator) / (4 * q_1 * q_2);
    }

    // ========== 3D Vector Operations ==========

    /**
     * @brief Calculates the dot product of two 3D vectors.
     *
     * @param v_1 First vector as std::vector<T> of size 3
     * @param v_2 Second vector as std::vector<T> of size 3
     * @return Dot product of the two vectors
     * @throws TrigonomError if vectors don't have size 3 or overflow occurs
     */
    template <typename T> constexpr T dot3d(const std::vector<T> &v_1, const std::vector<T> &v_2) {
        validate_vector_size(v_1, 3);
        validate_vector_size(v_2, 3);
        validate_no_overflow_multiply(v_1[0], v_2[0], "v_1[0] * v_2[0] in dot3d");
        validate_no_overflow_multiply(v_1[1], v_2[1], "v_1[1] * v_2[1] in dot3d");
        validate_no_overflow_multiply(v_1[2], v_2[2], "v_1[2] * v_2[2] in dot3d");
        return v_1[0] * v_2[0] + v_1[1] * v_2[1] + v_1[2] * v_2[2];
    }

    /**
     * @brief Calculates the cross product of two 3D vectors.
     *
     * @param v_1 First vector as std::vector<T> of size 3
     * @param v_2 Second vector as std::vector<T> of size 3
     * @return Cross product of the two vectors
     * @throws TrigonomError if vectors don't have size 3 or overflow occurs
     */
    template <typename T> constexpr std::vector<T> cross3d(const std::vector<T> &v_1, const std::vector<T> &v_2) {
        validate_vector_size(v_1, 3);
        validate_vector_size(v_2, 3);
        
        // Validate all multiplications
        validate_no_overflow_multiply(v_1[1], v_2[2], "v_1[1] * v_2[2] in cross3d");
        validate_no_overflow_multiply(v_1[2], v_2[1], "v_1[2] * v_2[1] in cross3d");
        validate_no_overflow_multiply(v_1[2], v_2[0], "v_1[2] * v_2[0] in cross3d");
        validate_no_overflow_multiply(v_1[0], v_2[2], "v_1[0] * v_2[2] in cross3d");
        validate_no_overflow_multiply(v_1[0], v_2[1], "v_1[0] * v_2[1] in cross3d");
        validate_no_overflow_multiply(v_1[1], v_2[0], "v_1[1] * v_2[0] in cross3d");
        
        return {
            v_1[1] * v_2[2] - v_1[2] * v_2[1],
            v_1[2] * v_2[0] - v_1[0] * v_2[2],
            v_1[0] * v_2[1] - v_1[1] * v_2[0]
        };
    }

    /**
     * @brief Calculates the quadrance (squared length) of a 3D vector.
     *
     * @param vec Vector as std::vector<T> of size 3
     * @return Quadrance of the vector
     * @throws TrigonomError if vector doesn't have size 3 or overflow occurs
     */
    template <typename T> constexpr T quad3d(const std::vector<T> &vec) {
        validate_vector_size(vec, 3);
        validate_no_overflow_square(vec[0], "vec[0] in quad3d");
        validate_no_overflow_square(vec[1], "vec[1] in quad3d");
        validate_no_overflow_square(vec[2], "vec[2] in quad3d");
        validate_no_overflow_add(vec[0] * vec[0], vec[1] * vec[1], "quad3d sum (first two)");
        validate_no_overflow_add(vec[0] * vec[0] + vec[1] * vec[1], vec[2] * vec[2], "quad3d sum (total)");
        return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
    }

    /**
     * @brief Calculates the spread between two 3D vectors.
     *
     * The spread is defined as 1 - (dot)^2 / (q1 * q2), which represents
     * the squared sine of the angle between vectors.
     *
     * @param v_1 First vector as std::vector<T> of size 3
     * @param v_2 Second vector as std::vector<T> of size 3
     * @return Spread between the two vectors
     * @throws TrigonomError if vectors don't have size 3, have zero length, or overflow occurs
     */
    template <typename T> constexpr T spread3d(const std::vector<T> &v_1, const std::vector<T> &v_2) {
        validate_vector_size(v_1, 3);
        validate_vector_size(v_2, 3);
        
        T q1 = quad3d(v_1);
        T q2 = quad3d(v_2);
        
        validate_non_zero(q1, "quad3d(v_1)");
        validate_non_zero(q2, "quad3d(v_2)");
        validate_no_overflow_multiply(q1, q2, "q1 * q2 in spread3d");
        
        T dot_val = dot3d(v_1, v_2);
        validate_no_overflow_square(dot_val, "dot_val in spread3d");
        return 1 - (dot_val * dot_val) / (q1 * q2);
    }

    /**
     * @brief Calculates the triple product of three 3D vectors.
     *
     * The triple product is the dot product of one vector with the cross product of the other two.
     * It represents the signed volume of the parallelepiped formed by the three vectors.
     *
     * @param v_1 First vector as std::vector<T> of size 3
     * @param v_2 Second vector as std::vector<T> of size 3
     * @param v_3 Third vector as std::vector<T> of size 3
     * @return Triple product (scalar)
     * @throws TrigonomError if vectors don't have size 3 or overflow occurs
     */
    template <typename T> 
    constexpr T triple_product(const std::vector<T> &v_1, const std::vector<T> &v_2, const std::vector<T> &v_3) {
        std::vector<T> cross_val = cross3d(v_1, v_2);
        return dot3d(cross_val, v_3);
    }

    // ========== Triangle Solving Utilities ==========

    /**
     * @brief Structure to represent a triangle with points and properties
     */
    template <typename T>
    struct Triangle {
        std::vector<T> a;  // First vertex
        std::vector<T> b;  // Second vertex
        std::vector<T> c;  // Third vertex
        T q_ab;            // Quadrance of side AB
        T q_bc;            // Quadrance of side BC
        T q_ca;            // Quadrance of side CA
        T quadrea;         // Quadrea (4 * area^2)
        T spread_a;        // Spread at vertex A
        T spread_b;        // Spread at vertex B
        T spread_c;        // Spread at vertex C
    };

    /**
     * @brief Creates a triangle from three 2D points
     *
     * @param a First point (2D vector)
     * @param b Second point (2D vector)
     * @param c Third point (2D vector)
     * @return Triangle structure with all computed properties
     * @throws TrigonomError if vectors don't have size 2, points are collinear, or overflow occurs
     */
    template <typename T>
    constexpr Triangle<T> create_triangle(const std::vector<T>& a, const std::vector<T>& b, const std::vector<T>& c) {
        validate_vector_size(a, 2);
        validate_vector_size(b, 2);
        validate_vector_size(c, 2);

        Triangle<T> tri;
        tri.a = a;
        tri.b = b;
        tri.c = c;

        // Calculate side vectors
        std::vector<T> ab = {b[0] - a[0], b[1] - a[1]};
        std::vector<T> bc = {c[0] - b[0], c[1] - b[1]};
        std::vector<T> ca = {a[0] - c[0], a[1] - c[1]};

        // Calculate quadrances
        tri.q_ab = quad(ab);
        tri.q_bc = quad(bc);
        tri.q_ca = quad(ca);

        // Calculate quadrea
        tri.quadrea = archimedes(tri.q_ab, tri.q_bc, tri.q_ca);

        // Validate triangle is non-degenerate
        validate_non_zero(tri.quadrea, "quadrea (collinear points)");

        // Calculate spreads
        tri.spread_a = spread_law(tri.q_ca, tri.q_ab, tri.q_bc);
        tri.spread_b = spread_law(tri.q_ab, tri.q_bc, tri.q_ca);
        tri.spread_c = spread_law(tri.q_bc, tri.q_ca, tri.q_ab);

        return tri;
    }

    /**
     * @brief Solves a triangle given two sides and the included spread (SAS case)
     *
     * @param q_1 First quadrance
     * @param q_2 Second quadrance
     * @param spread Included spread between the sides
     * @return Triangle structure with all computed properties
     * @throws TrigonomError if inputs are invalid or overflow occurs
     */
    template <typename T>
    constexpr Triangle<T> solve_triangle_sas(const T& q_1, const T& q_2, const T& spread) {
        validate_non_negative(q_1, "q_1");
        validate_non_negative(q_2, "q_2");
        validate_non_negative(spread, "spread");
        validate_non_zero(q_1, "q_1");
        validate_non_zero(q_2, "q_2");
        validate_non_negative(spread, "spread");

        // Calculate third quadrance using triple quad formula
        // Note: triple_quad_formula returns the squared third quadrance
        T q_3_squared = triple_quad_formula(q_1, q_2, spread);
        
        // Take square root to get the actual third quadrance
        if constexpr (std::is_floating_point_v<T>) {
            if (q_3_squared < 0) {
                throw TrigonomError("Invalid triangle: third quadrance squared is negative");
            }
        }
        
        T q_3 = std::sqrt(q_3_squared);
        
        // Verify triangle is valid (positive quadrea)
        T q = archimedes(q_1, q_2, q_3);
        if (q < T(0)) {
            throw TrigonomError("Invalid triangle: quadrea is negative for SAS case");
        }

        // Calculate other spreads
        T spread_2 = spread_law(q_2, q_3, q_1);
        T spread_3 = spread_law(q_3, q_1, q_2);

        // Create triangle with vertex at origin
        Triangle<T> tri;
        tri.a = {T(0), T(0)};
        tri.b = {q_1, T(0)};  // Side AB along x-axis
        tri.c = {q_1 * (1 - spread), std::sqrt(q_1 * q_2 * spread)};  // Point C

        tri.q_ab = q_1;
        tri.q_bc = q_2;
        tri.q_ca = q_3;
        tri.quadrea = q;
        tri.spread_a = spread_3;
        tri.spread_b = spread_2;
        tri.spread_c = spread;

        return tri;
    }

    /**
     * @brief Solves a triangle given three quadrances (SSS case)
     *
     * @param q_1 First quadrance
     * @param q_2 Second quadrance
     * @param q_3 Third quadrance
     * @return Triangle structure with all computed properties
     * @throws TrigonomError if inputs don't form a valid triangle or overflow occurs
     */
    template <typename T>
    constexpr Triangle<T> solve_triangle_sss(const T& q_1, const T& q_2, const T& q_3) {
        validate_non_negative(q_1, "q_1");
        validate_non_negative(q_2, "q_2");
        validate_non_negative(q_3, "q_3");
        validate_non_zero(q_1, "q_1");
        validate_non_zero(q_2, "q_2");
        validate_non_zero(q_3, "q_3");

        // Calculate quadrea to validate triangle
        T q = archimedes(q_1, q_2, q_3);
        validate_non_zero(q, "quadrea (invalid triangle)");

        // Calculate spreads
        T spread_1 = spread_law(q_1, q_2, q_3);
        T spread_2 = spread_law(q_2, q_3, q_1);
        T spread_3 = spread_law(q_3, q_1, q_2);

        // Create triangle with vertex at origin
        Triangle<T> tri;
        tri.a = {T(0), T(0)};
        tri.b = {q_1, T(0)};
        tri.c = {q_1 * (1 - spread_1), std::sqrt(q_1 * q_2 * spread_1)};

        tri.q_ab = q_1;
        tri.q_bc = q_2;
        tri.q_ca = q_3;
        tri.quadrea = q;
        tri.spread_a = spread_3;
        tri.spread_b = spread_2;
        tri.spread_c = spread_1;

        return tri;
    }

    /**
     * @brief Solves a triangle given two spreads and a quadrance (SSA case)
     *
     * @param spread_1 First spread
     * @param spread_2 Second spread
     * @param q_1 Quadrance between the spreads
     * @return Triangle structure with all computed properties
     * @throws TrigonomError if inputs don't form a valid triangle or overflow occurs
     */
    template <typename T>
    constexpr Triangle<T> solve_triangle_ssa(const T& spread_1, const T& spread_2, const T& q_1) {
        validate_non_negative(spread_1, "spread_1");
        validate_non_negative(spread_2, "spread_2");
        validate_non_negative(q_1, "q_1");
        validate_non_zero(q_1, "q_1");
        validate_non_zero(spread_2, "spread_2");

        // Calculate second quadrance
        T q_2 = q_1 * spread_1 / spread_2;
        validate_non_negative(q_2, "q_2 (calculated)");

        // Calculate third quadrance
        T q_3 = triple_quad_formula(q_1, q_2, spread_1);

        // Calculate quadrea
        T q = archimedes(q_1, q_2, q_3);
        validate_non_zero(q, "quadrea (invalid triangle)");

        // Calculate remaining spread
        T spread_3 = spread_law(q_3, q_1, q_2);

        // Create triangle
        Triangle<T> tri;
        tri.a = {T(0), T(0)};
        tri.b = {q_1, T(0)};
        tri.c = {q_1 * (1 - spread_1), std::sqrt(q_1 * q_2 * spread_1)};

        tri.q_ab = q_1;
        tri.q_bc = q_2;
        tri.q_ca = q_3;
        tri.quadrea = q;
        tri.spread_a = spread_3;
        tri.spread_b = spread_2;
        tri.spread_c = spread_1;

        return tri;
    }

    // ========== Coordinate Transformations ==========

    /**
     * @brief Rotates a 2D vector by a given spread (sine squared of angle)
     *
     * @param vec Vector to rotate (2D)
     * @param spread Spread representing rotation (sine squared of angle)
     * @return Rotated vector
     * @throws TrigonomError if vector doesn't have size 2 or spread is invalid
     */
    template <typename T>
    constexpr std::vector<T> rotate_2d(const std::vector<T>& vec, const T& spread) {
        validate_vector_size(vec, 2);
        validate_non_negative(spread, "spread");
        validate_non_zero(spread, "spread");  // Non-zero rotation

        T cos_sq = 1 - spread;
        T cos_val = std::sqrt(cos_sq);
        T sin_val = std::sqrt(spread);

        return {
            cos_val * vec[0] - sin_val * vec[1],
            sin_val * vec[0] + cos_val * vec[1]
        };
    }

    /**
     * @brief Translates a 2D vector by a translation vector
     *
     * @param vec Vector to translate (2D)
     * @param translation Translation vector (2D)
     * @return Translated vector
     * @throws TrigonomError if vectors don't have size 2
     */
    template <typename T>
    constexpr std::vector<T> translate_2d(const std::vector<T>& vec, const std::vector<T>& translation) {
        validate_vector_size(vec, 2);
        validate_vector_size(translation, 2);

        return {
            vec[0] + translation[0],
            vec[1] + translation[1]
        };
    }

    /**
     * @brief Scales a 2D vector by a scalar factor
     *
     * @param vec Vector to scale (2D)
     * @param scale Scaling factor
     * @return Scaled vector
     * @throws TrigonomError if vector doesn't have size 2 or overflow occurs
     */
    template <typename T>
    constexpr std::vector<T> scale_2d(const std::vector<T>& vec, const T& scale) {
        validate_vector_size(vec, 2);
        validate_no_overflow_multiply(vec[0], scale, "vec[0] * scale in scale_2d");
        validate_no_overflow_multiply(vec[1], scale, "vec[1] * scale in scale_2d");

        return {
            vec[0] * scale,
            vec[1] * scale
        };
    }

    /**
     * @brief Rotates a 3D vector around the x-axis by a given spread
     *
     * @param vec Vector to rotate (3D)
     * @param spread Spread representing rotation (sine squared of angle)
     * @return Rotated vector
     * @throws TrigonomError if vector doesn't have size 3 or spread is invalid
     */
    template <typename T>
    constexpr std::vector<T> rotate_3d_x(const std::vector<T>& vec, const T& spread) {
        validate_vector_size(vec, 3);
        validate_non_negative(spread, "spread");
        validate_non_zero(spread, "spread");

        T cos_sq = 1 - spread;
        T cos_val = std::sqrt(cos_sq);
        T sin_val = std::sqrt(spread);

        return {
            vec[0],
            cos_val * vec[1] - sin_val * vec[2],
            sin_val * vec[1] + cos_val * vec[2]
        };
    }

    /**
     * @brief Rotates a 3D vector around the y-axis by a given spread
     *
     * @param vec Vector to rotate (3D)
     * @param spread Spread representing rotation (sine squared of angle)
     * @return Rotated vector
     * @throws TrigonomError if vector doesn't have size 3 or spread is invalid
     */
    template <typename T>
    constexpr std::vector<T> rotate_3d_y(const std::vector<T>& vec, const T& spread) {
        validate_vector_size(vec, 3);
        validate_non_negative(spread, "spread");
        validate_non_zero(spread, "spread");

        T cos_sq = 1 - spread;
        T cos_val = std::sqrt(cos_sq);
        T sin_val = std::sqrt(spread);

        return {
            cos_val * vec[0] + sin_val * vec[2],
            vec[1],
            -sin_val * vec[0] + cos_val * vec[2]
        };
    }

    /**
     * @brief Rotates a 3D vector around the z-axis by a given spread
     *
     * @param vec Vector to rotate (3D)
     * @param spread Spread representing rotation (sine squared of angle)
     * @return Rotated vector
     * @throws TrigonomError if vector doesn't have size 3 or spread is invalid
     */
    template <typename T>
    constexpr std::vector<T> rotate_3d_z(const std::vector<T>& vec, const T& spread) {
        validate_vector_size(vec, 3);
        validate_non_negative(spread, "spread");
        validate_non_zero(spread, "spread");

        T cos_sq = 1 - spread;
        T cos_val = std::sqrt(cos_sq);
        T sin_val = std::sqrt(spread);

        return {
            cos_val * vec[0] - sin_val * vec[1],
            sin_val * vec[0] + cos_val * vec[1],
            vec[2]
        };
    }

}  // namespace rattrig