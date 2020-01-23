#include "analysis.h"
#include "rawfile.h"

void test();

int main()
{
    test();
}

void test()
{
    std::string fname1 = "./brain_float_128-128-128.raw";
    std::string fname2 = "./Dm20_n2_DeconvolutionWithSensitivityCorrectionDm90n2_TEW_FWHM4mm_Brain_white4000000_gray12000000_Dia5mm_Iter100_6Proj_float_128-128-128.raw";

    const int size = 128;

    std::vector<float> data1(size * size * size, 0.);
    std::vector<float> data2(size * size * size, 0.);

    read_rawfile(fname1, data1);
    read_rawfile(fname2, data2);

    scale_pixel_value(data1, data2);

    write_rawfile("Scaling_" + fname2, data2);

    const float c1 = 0.001, c2 = 0.05;

    std::cout << "SSIM = " << get_ssim(data1, data2, c1, c2) << std::endl; 
    std::cout << "PSNR = " << get_psnr(data1, data2) << std::endl; 
}

/* ----- function list ----- */
/*
template <typename T> void read_rawfile(std::string fname, std::vector<T>& image);
機能: ファイル名 fname の raw ファイルを読み取り, ベクタ image に格納する関数 

template <typename T> void write_rawfile(std::string fname, std::vector<T>& image);
機能: ベクタ image の内容を ファイル名 fname の raw ファイルに書き込む関数 

template <typename T> T get_average(std::vector<T>& data);
機能: data の平均値を返す関数

template <typename T> T get_dispersion(std::vector<T>& data);
機能: data の分散を返す関数

template <typename T> T get_unbiased_dispersion(std::vector<T>& data);
機能: data の不偏分散を返す関数

template <typename T> T get_convariance(std::vector<T>& data1, std::vector<T>& data2);
機能: data1 と data2 の共分散を返す関数

template <typename T> T get_unbiased_convariance(std::vector<T>& data1, std::vector<T>& data2);
機能: data1 と data2 の不偏共分散を返す関数

template <typename T> T get_standard_deviation(std::vector<T>& data);
機能: data の標準偏差を返す関数

template <typename T> T get_unbiased_standard_deviation(std::vector<T>& data);
機能: data の不偏標準偏差を返す関数

template <typename T> T get_mean_square_error(std::vector<T>& data1, std::vector<T>& data2);
機能: data1 と data2 の mean square error を返す関数

template <typename T> T get_inner_product(std::vector<T>& data1, std::vector<T>& data2);
機能: data1 と data2 の内積を返す関数

template <typename T> void scale_pixel_value(std::vector<T>& data1, std::vector<T>& data2);
機能: data2 を data1 との mean square error が最小値になるようにスケーリングする関数

*/
