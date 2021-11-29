/*
 * Cursus CentraleSupélec - Dominante Mathématiques et Data Sciences
 * 3MD1080 - C++ - TP n°3
 *
 * compute_pi_montecarlo.cpp
 * c++ -std=c++20 -o compute_pi_montecarlo compute_pi_montecarlo.cpp -lpthread
 */

#include <chrono>
#include <future>
#include <iostream>
#include <iomanip>
// #include <numbers>
#include <random>
#include <string>
#include <thread>

#include <cctype>
#include <cmath>
#include <cstdlib>

using FloatKind = long double;
const FloatKind pi{3.14159265358979323846};

FloatKind next_random()
{
    static thread_local std::mt19937 generator{std::random_device{}()};
    std::uniform_real_distribution<FloatKind> distribution{};
    return distribution(generator);
};

unsigned long nb_points_inside_unit_circle(unsigned long nb_points)
{
    FloatKind random_x{};
    FloatKind random_y{};
    unsigned long result = 0;
    for (unsigned long i = 0; i < nb_points; i++)
    {
        random_x = next_random();
        random_y = next_random();
        if (random_x * random_x + random_y * random_y <= 1)
        {
            result++;
        };
    };
    return result;
};

FloatKind compute_pi(unsigned long nb_points)
{
    FloatKind total = static_cast<FloatKind>(nb_points);
    FloatKind inside_circle = static_cast<FloatKind>(nb_points_inside_unit_circle(nb_points));
    return 4 * inside_circle / total;
}

//test11
void test_pi_computation(unsigned long nb_points)
{
    FloatKind error{std::abs(pi - compute_pi(nb_points))};
    std::cout << "Error is: " << error << "\n\n";
}

//test12

// FLOAT:
// With nb_points = 70000000 and -o, execution time is ~22s.
// With nb_points = 70000000 and -O, execution time is ~12s.
// With nb_points = 70000000 and -O2, execution time is ~10s.
// With nb_points = 70000000 and -O3, execution time is ~10s.

// DOUBLE:
// With nb_points = 70000000 and -o, execution time is ~25s.

// LONG DOUBLE:
// With nb_points = 70000000 and -o, execution time is ~33s.
void test_execution_time(unsigned long nb_points)
{
    auto start = std::chrono::high_resolution_clock::now();
    FloatKind error{std::abs(pi - compute_pi(nb_points))};
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Error is: " << error << "\n\n";
    std::cout << "Execution time is: " << duration.count() << "ms\n\n";
}

//test14

// FLOAT:
// Max variability is ~10^-2

// DOUBLE:
// Max variability is ~10^-2

// LONG DOUBLE:
// Max variability still is ~10^-2
void test_variability(unsigned long nb_points)
{
    FloatKind greatest_difference{0};
    FloatKind res{};
    for (int i = 0; i < 10; i++)
    {
        res = std::abs(pi - compute_pi(nb_points));
        if (res > greatest_difference)
        {
            greatest_difference = res;
        }
    }
    std::cout << "Greatest estimation error is: " << greatest_difference << "\n\n";
}

int main(int argc, char *argv[])
{
    unsigned long nb_points = std::stoull(argv[1]);
    // test_pi_computation(nb_points);
    // test_execution_time(nb_points);
    // test_variability(nb_points);
};