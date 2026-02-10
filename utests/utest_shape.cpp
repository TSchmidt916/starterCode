#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#define private public
#include "shape.h"
#include "sphere.h"
#define private private

//1
TEST_CASE( "sphere default constructor" )
{
    sphere s;
    float eps = 1e-3;

    REQUIRE_THAT(s.center.x(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(s.center.y(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(s.center.z(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(s.radius, Catch::Matchers::WithinAbs(1.0f, eps));
}

//2
TEST_CASE( "sphere parameterized constructor" )
{
    vec3 center(1.0f, 2.0f, 3.0f);
    float radius = 4.0f;
    sphere s(center, radius);
    float eps = 1e-3;

    REQUIRE_THAT(s.center.x(), Catch::Matchers::WithinAbs(1.0f, eps));
    REQUIRE_THAT(s.center.y(), Catch::Matchers::WithinAbs(2.0f, eps));
    REQUIRE_THAT(s.center.z(), Catch::Matchers::WithinAbs(3.0f, eps));
    REQUIRE_THAT(s.radius, Catch::Matchers::WithinAbs(4.0f, eps));
}

//3
TEST_CASE( "sphere intersection with ray hitting the sphere" )
{
    vec3 center(0.0f, 0.0f, -5.0f);
    float radius = 1.0f;
    sphere s(center, radius);
    float tmin = 0.001f;
    float tmax = std::numeric_limits<float>::infinity();

    point3 origin(0.0f, 0.0f, 0.0f);
    vec3 direction(0.0f, 0.0f, -1.0f);
    ray r(origin, direction);

    REQUIRE(s.intersect(r, tmin, tmax) == true);
}

//4
TEST_CASE( "sphere intersection with ray missing the sphere" )
{
    vec3 center(0.0f, 0.0f, -5.0f);
    float radius = 1.0f;
    sphere s(center, radius);
    float tmin = 0.001f;
    float tmax = std::numeric_limits<float>::infinity();

    point3 origin(0.0f, 0.0f, 0.0f);
    vec3 direction(0.0f, 1.0f, 0.0f);
    ray r(origin, direction);

    REQUIRE(s.intersect(r, tmin, tmax) == false);
}

//5
TEST_CASE( "sphere intersection with ray tangent to the sphere" )
{
    vec3 center(0.0f, 1.0f, -5.0f);
    float radius = 1.0f;
    sphere s(center, radius);
    float tmin = 0.001f;
    float tmax = std::numeric_limits<float>::infinity();

    point3 origin(0.0f, 0.0f, 0.0f);
    vec3 direction(0.0f, 1.0f, -5.0f);
    ray r(origin, direction);

    REQUIRE(s.intersect(r, tmin, tmax) == true);
}

//6
TEST_CASE( "sphere intersection with ray originating inside the sphere" )
{
    vec3 center(0.0f, 0.0f, 0.0f);
    float radius = 2.0f;
    sphere s(center, radius);
    float tmin = 0.001f;
    float tmax = std::numeric_limits<float>::infinity();

    point3 origin(0.0f, 0.0f, 1.0f);
    vec3 direction(0.0f, 0.0f, 1.0f);
    ray r(origin, direction);

    REQUIRE(s.intersect(r, tmin, tmax) == true);
}