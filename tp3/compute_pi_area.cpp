/*
 * Cursus CentraleSupélec - Dominante Mathématiques et Data Sciences
 * 3MD1080 - C++ - TP n°3
 *
 * compute_pi_area.cpp
 * c++ -std=c++20 -o compute_pi_area -I/opt/tbb/include compute_pi_area.cpp -L/opt/tbb/lib/intel64/gcc4.8 -ltbb
 */

#include <chrono>
#include <iostream>
#include <iomanip>
// #include <numbers>
#include <string>
#include <functional>

#include <cmath>
#include <cstdlib>

// #include <tbb/tbb.h>

using FloatKind = double;
const FloatKind pi{3.14159265358979323846};

FloatKind one_over_one_plus_x_squared(FloatKind x)
{
    return 1.0 / (1.0 + x * x);
};

FloatKind compute_area(std::function<FloatKind(FloatKind)> func, FloatKind x, FloatKind width)
{
    return func(x) * width;
};

FloatKind compute_integral(std::function<FloatKind(FloatKind)> func, FloatKind begin, FloatKind end, unsigned long nb_points)
{
    const FloatKind step_size = (end - begin) / nb_points;
    FloatKind area{0};
    for (int i = 0; i < nb_points; i++)
    {
        area = area + compute_area(func, begin + i * step_size, step_size);
    }
    return area;
}

FloatKind compute_pi(unsigned long nb_points)
{
    return 4 * compute_integral(one_over_one_plus_x_squared, 0, 1, nb_points);
}

// test3
// For nb_points = e9, and parameter -O3, execution time is ~9s and precision is ~e-9
void test_pi_computation(unsigned long nb_points)
{
    auto start = std::chrono::high_resolution_clock::now();
    FloatKind error{std::abs(pi - compute_pi(nb_points))};
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Error is: " << error << "\n\n";
    std::cout << "Execution time is: " << duration.count() << "s\n\n";
}

int main(int argc, char *argv[])
{
    unsigned long nb_points = std::stoull(argv[1]);
    test_pi_computation(nb_points);
};
