#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "ray.h"

//1
TEST_CASE( "ray origin and direction" )
{
    point3 origin(1, 2, 3);
    vec3 direction(4, 5, 6);

    ray r(origin, direction);

    float eps = 1e-3;
    REQUIRE_THAT(r.origin().x(), Catch::Matchers::WithinAbs(1, eps));
    REQUIRE_THAT(r.origin().y(), Catch::Matchers::WithinAbs(2, eps));
    REQUIRE_THAT(r.origin().z(), Catch::Matchers::WithinAbs(3, eps));

    REQUIRE_THAT(r.direction().x(), Catch::Matchers::WithinAbs(4, eps));
    REQUIRE_THAT(r.direction().y(), Catch::Matchers::WithinAbs(5, eps));
    REQUIRE_THAT(r.direction().z(), Catch::Matchers::WithinAbs(6, eps));
}

//2
TEST_CASE( "ray at(t) function" )
{
    point3 origin(0, 0, 0);
    vec3 direction(1, 2, 3);

    ray r(origin, direction);

    float t = 2.0f;
    point3 p = r.at(t);

    float eps = 1e-3;
    REQUIRE_THAT(p.x(), Catch::Matchers::WithinAbs(2.0f, eps));
    REQUIRE_THAT(p.y(), Catch::Matchers::WithinAbs(4.0f, eps));
    REQUIRE_THAT(p.z(), Catch::Matchers::WithinAbs(6.0f, eps));
}

//3
TEST_CASE( "ray at(t) with negative t" )
{
    point3 origin(1, 1, 1);
    vec3 direction(1, 1, 1);

    ray r(origin, direction);

    float t = -1.0f;
    point3 p = r.at(t);

    float eps = 1e-3;
    REQUIRE_THAT(p.x(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(p.y(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(p.z(), Catch::Matchers::WithinAbs(0.0f, eps));
}

//4
TEST_CASE( "ray at(t) with zero direction" )
{
    point3 origin(5, 5, 5);
    vec3 direction(0, 0, 0);

    ray r(origin, direction);

    float t = 10.0f;
    point3 p = r.at(t);

    float eps = 1e-3;
    REQUIRE_THAT(p.x(), Catch::Matchers::WithinAbs(5.0f, eps));
    REQUIRE_THAT(p.y(), Catch::Matchers::WithinAbs(5.0f, eps));
    REQUIRE_THAT(p.z(), Catch::Matchers::WithinAbs(5.0f, eps));
}

//5
TEST_CASE( "ray at(t) with non-unit direction" )
{
    point3 origin(0, 0, 0);
    vec3 direction(2, 0, 0);

    ray r(origin, direction);

    float t = 3.0f;
    point3 p = r.at(t);

    float eps = 1e-3;
    REQUIRE_THAT(p.x(), Catch::Matchers::WithinAbs(6.0f, eps));
    REQUIRE_THAT(p.y(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(p.z(), Catch::Matchers::WithinAbs(0.0f, eps));
}

//6
TEST_CASE( "ray at(t) with fractional t" )
{
    point3 origin(1, 1, 1);
    vec3 direction(0, 2, 0);

    ray r(origin, direction);

    float t = 0.5f;
    point3 p = r.at(t);

    float eps = 1e-3;
    REQUIRE_THAT(p.x(), Catch::Matchers::WithinAbs(1.0f, eps));
    REQUIRE_THAT(p.y(), Catch::Matchers::WithinAbs(2.0f, eps));
    REQUIRE_THAT(p.z(), Catch::Matchers::WithinAbs(1.0f, eps));
}

//7
TEST_CASE( "ray at(t) with large t" )
{
    point3 origin(1, 1, 1);
    vec3 direction(1, 1, 1);

    ray r(origin, direction);

    float t = 1e6f;
    point3 p = r.at(t);

    float eps = 1e-1; // larger epsilon for large values
    REQUIRE_THAT(p.x(), Catch::Matchers::WithinAbs(1.0f + 1e6f, eps));
    REQUIRE_THAT(p.y(), Catch::Matchers::WithinAbs(1.0f + 1e6f, eps));
    REQUIRE_THAT(p.z(), Catch::Matchers::WithinAbs(1.0f + 1e6f, eps));
}

//8
TEST_CASE( "ray at(t) with small t" )
{
    point3 origin(1, 1, 1);
    vec3 direction(1, 1, 1);

    ray r(origin, direction);

    float t = 1e-6f;
    point3 p = r.at(t);

    float eps = 1e-6f;
    REQUIRE_THAT(p.x(), Catch::Matchers::WithinAbs(1.0f + 1e-6f, eps));
    REQUIRE_THAT(p.y(), Catch::Matchers::WithinAbs(1.0f + 1e-6f, eps));
    REQUIRE_THAT(p.z(), Catch::Matchers::WithinAbs(1.0f + 1e-6f, eps));
}

//9
TEST_CASE( "ray at(t) with non-orthogonal direction" )
{
    point3 origin(0, 0, 0);
    vec3 direction(1, 2, 3);

    ray r(origin, direction);

    float t = 1.0f;
    point3 p = r.at(t);

    float eps = 1e-3;
    REQUIRE_THAT(p.x(), Catch::Matchers::WithinAbs(1.0f, eps));
    REQUIRE_THAT(p.y(), Catch::Matchers::WithinAbs(2.0f, eps));
    REQUIRE_THAT(p.z(), Catch::Matchers::WithinAbs(3.0f, eps));
}

//10
TEST_CASE( "ray at(t) with origin at negative coordinates" )
{
    point3 origin(-1, -1, -1);
    vec3 direction(1, 1, 1);

    ray r(origin, direction);

    float t = 2.0f;
    point3 p = r.at(t);

    float eps = 1e-3;
    REQUIRE_THAT(p.x(), Catch::Matchers::WithinAbs(1.0f, eps));
    REQUIRE_THAT(p.y(), Catch::Matchers::WithinAbs(1.0f, eps));
    REQUIRE_THAT(p.z(), Catch::Matchers::WithinAbs(1.0f, eps));
}

//11
TEST_CASE("Immutability of ray origin and direction") {
    point3 origin(1, 2, 3);
    vec3 direction(4, 5, 6);

    ray r(origin, direction);

    // Attempt to modify origin and direction through the returned references
    const point3& origRef = r.origin();
    const vec3& dirRef = r.direction();

    // The following lines should cause compilation errors if uncommented,
    // ensuring immutability.
    // origRef.e[0] = 10; // Uncommenting this line should cause a compilation error
    // dirRef.e[1] = 20;  // Uncommenting this line should cause a compilation error

    // Instead, we verify that the original values remain unchanged
    float eps = 1e-3;
    REQUIRE_THAT(r.origin().x(), Catch::Matchers::WithinAbs(1, eps));
    REQUIRE_THAT(r.origin().y(), Catch::Matchers::WithinAbs(2, eps));
    REQUIRE_THAT(r.origin().z(), Catch::Matchers::WithinAbs(3, eps));

    REQUIRE_THAT(r.direction().x(), Catch::Matchers::WithinAbs(4, eps));
    REQUIRE_THAT(r.direction().y(), Catch::Matchers::WithinAbs(5, eps));
    REQUIRE_THAT(r.direction().z(), Catch::Matchers::WithinAbs(6, eps));
}