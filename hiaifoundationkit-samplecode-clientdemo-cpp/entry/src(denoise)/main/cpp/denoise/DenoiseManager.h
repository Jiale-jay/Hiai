#ifndef DENOISEMANAGER_H
#define DENOISEMANAGER_H

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <hiai_ai.h> // HiAI SDK 头文件

class DenoiseManager {
public:
    bool loadModel(const std::string& modelPath);
    bool denoiseImage(const cv::Mat& input, cv::Mat& output);
    double calculatePSNR(const cv::Mat& original, const cv::Mat& denoised);
    double calculateSSIM(const cv::Mat& original, const cv::Mat& denoised);

private:
    HIAI_ModelHandle modelHandle = nullptr; // HiAI 模型句柄
};

#endif