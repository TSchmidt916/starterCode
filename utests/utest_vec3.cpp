#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "vec3.h"

//1
TEST_CASE( "vec3 dot product" )
{
    vec3 a(1, 2, 3);
    vec3 b(4, 5, 6);

    float result = dot(a, b);

    float eps = 1e-3;
    REQUIRE_THAT(result, Catch::Matchers::WithinAbs(32, eps));
}


//2
TEST_CASE( "vec3 cross product" )
{
    vec3 a(1, 2, 3);
    vec3 b(4, 5, 6);

    vec3 c = cross(a, b);

    float eps = 1e-3;
    REQUIRE_THAT(c.x(), Catch::Matchers::WithinAbs(-3, eps));
    REQUIRE_THAT(c.y(), Catch::Matchers::WithinAbs(6, eps));
    REQUIRE_THAT(c.z(), Catch::Matchers::WithinAbs(-3, eps));
}

//3
TEST_CASE( "vec3 addition" )
{
    vec3 a(1, 1, 1);
    vec3 b(2, 3, 4);

    vec3 c = a + b;

    float eps = 1e-3;
    REQUIRE_THAT(c.x(), Catch::Matchers::WithinAbs(3, eps));
    REQUIRE_THAT(c.y(), Catch::Matchers::WithinAbs(4, eps));
    REQUIRE_THAT(c.z(), Catch::Matchers::WithinAbs(5, eps));
}

//4
TEST_CASE( "vec3 subtraction" )
{
    vec3 a(1, 1, 1);
    vec3 b(2, 3, 4);

    vec3 c = a - b;

    float eps = 1e-3;
    REQUIRE_THAT(c.x(), Catch::Matchers::WithinAbs(-1, eps));
    REQUIRE_THAT(c.y(), Catch::Matchers::WithinAbs(-2, eps));
    REQUIRE_THAT(c.z(), Catch::Matchers::WithinAbs(-3, eps));
}

//5
TEST_CASE( "vec3 multiplication" )
{
    vec3 a(1, 2, 3);
    vec3 b(2, 3, 4);

    vec3 c = a * b;

    float eps = 1e-3;
    REQUIRE_THAT(c.x(), Catch::Matchers::WithinAbs(2, eps));
    REQUIRE_THAT(c.y(), Catch::Matchers::WithinAbs(6, eps));
    REQUIRE_THAT(c.z(), Catch::Matchers::WithinAbs(12, eps));
}

TEST_CASE("vec3 unit vector")
{
    vec3 a(3, 4, 0);
    float len = a.length();
    vec3 unit_a = a / len;

    float eps = 1e-3;
    REQUIRE_THAT(unit_a.length(), Catch::Matchers::WithinAbs(1.0f, eps));
    REQUIRE_THAT(unit_a.x(), Catch::Matchers::WithinAbs(0.6f, eps));
    REQUIRE_THAT(unit_a.y(), Catch::Matchers::WithinAbs(0.8f, eps));
    REQUIRE_THAT(unit_a.z(), Catch::Matchers::WithinAbs(0.0f, eps));
}