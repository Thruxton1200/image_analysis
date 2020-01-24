#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <cmath>

// ----- template functions ----- //
template <typename T> T get_average(std::vector<T>& data);
template <typename T> T get_dispersion(std::vector<T>& data);
template <typename T> T get_unbiased_dispersion(std::vector<T>& data);
template <typename T> T get_covariance(std::vector<T>& data1, std::vector<T>& data2);
template <typename T> T get_unbiased_covariance(std::vector<T>& data1, std::vector<T>& data2);
template <typename T> T get_standard_deviation(std::vector<T>& data);
template <typename T> T get_mean_square_error(std::vector<T>& data1, std::vector<T>& data2);

template <typename T> T calculate_inner_product(std::vector<T>& data1, std::vector<T>& data2);
template <typename T> void scale_pixel_value(std::vector<T>& data1, std::vector<T>& data2);
template <typename T> T get_ssim(std::vector<T>& data1, std::vector<T>& data2, T c1, T c2);
template <typename T> T get_psnr(std::vector<T>& data1, std::vector<T>& data2);
template <typename T> T get_total_value(std::vector<T>& data);

// ----- template functions ---- //
template <typename T> T get_average(std::vector<T>& data) { return std::accumulate(data.begin(), data.end(), 0.) / data.size(); }

template <typename T> T get_dispersion(std::vector<T>& data)
{
    T average = get_average(data), dispersion = 0.;
    
    for (auto it = std::begin(data); it != std::end(data); it++ ) dispersion += (*it - average) * (*it - average); 

    return ( dispersion / data.size() );
}

template <typename T> T get_unbiased_dispersion(std::vector<T>& data)
{
    T average = get_average(data), unbiased_dispersion = 0.;
    
    for (auto it = std::begin(data); it != std::end(data); it++ ) unbiased_dispersion += (*it - average) * (*it - average); 

    return ( unbiased_dispersion / ( data.size() - 1.) );
}

template <typename T> T get_covariance(std::vector<T>& data1, std::vector<T>& data2)
{
    T average1 = get_average(data1);
    T average2 = get_average(data2);
    T convariance = 0.;
    
    if ( data1.size() != data2.size() ) std::cout << "Error:: size of data1 is not equal to size of data2." << std::endl;
    
    for (int i = 0; i < data1.size(); i++) convariance += ( data1[i] - average1 ) * ( data2[i] - average2 );

    return ( convariance / data1.size() );
}

template <typename T> T get_unbiased_covariance(std::vector<T>& data1, std::vector<T>& data2)
{
    T average1 = get_average(data1);
    T average2 = get_average(data2);
    T unbiased_convariance = 0.;
    
    if ( data1.size() != data2.size() ) std::cout << "Error:: size of data1 is not equal to size of data2." << std::endl;
    
    for (int i = 0; i < data1.size(); i++) unbiased_convariance += ( data1[i] - average1 ) * ( data2[i] - average2 );
    
    return ( unbiased_convariance / ( data1.size() - 1.) );
}

template <typename T> T get_standard_deviation(std::vector<T>& data) { return sqrt( get_dispersion(data) ); }

template <typename T> T get_unbiased_standard_deviation(std::vector<T>& data) { return sqrt( get_unbiased_dispersion(data) ); }


template <typename T> T get_mean_square_error(std::vector<T>& data1, std::vector<T>& data2)
{
    T mse = 0.;

    if ( data1.size() != data2.size() ) std::cout << "Error:: size of data1 is not equal to size of data2." << std::endl;
    
    for (int i = 0; i < data1.size(); i++) mse += ( data1[i] - data2[i] ) * ( data1[i] - data2[i] );

    return ( mse / data1.size() );
}

template <typename T> T calculate_inner_product(std::vector<T>& data1, std::vector<T>& data2)
{
    T inner_product = 0.;

    if ( data1.size() != data2.size() ) std::cout << "Error:: size of data1 is not equal to size of data2." << std::endl;
    
    for (int i = 0; i < data1.size(); i++) inner_product += data1[i] * data2[i];

    return inner_product;
}

template <typename T> void scale_pixel_value(std::vector<T>& data1, std::vector<T>& data2)
{
    T scale = calculate_inner_product(data1, data2) / calculate_inner_product(data2, data2);

    for (auto it = std::begin(data2); it != std::end(data2); it++ ) *it *= scale; 
}

template <typename T> T get_ssim(std::vector<T>& data1, std::vector<T>& data2, T c1, T c2)
{
    T mu1 = get_average(data1), mu2 = get_average(data2), d1 = get_unbiased_dispersion(data1), d2 = get_unbiased_dispersion(data2);
    T c12 = get_unbiased_covariance(data1, data2);

    return ( 2. * mu1 * mu2 + c1 ) * ( 2. * c12 + c2 ) / (( mu1 * mu1 + mu2 * mu2 + c1 ) * ( d1 + d2 + c2 ));
}

template <typename T> T get_psnr(std::vector<T>& data1, std::vector<T>& data2)
{
    T mse = get_mean_square_error(data1, data2), max = 0.;
    
    for (int i = 0; i < data1.size(); i++) {
        if ( max < data1[i] )
            max = data1[i];
    }

    T psnr = 10. * log(max * max / mse) / log(10.);

    return psnr; 
}

template <typename T> T get_total_value(std::vector<T>& data) { return std::accumulate(data.begin(), data.end(), 0.); }
