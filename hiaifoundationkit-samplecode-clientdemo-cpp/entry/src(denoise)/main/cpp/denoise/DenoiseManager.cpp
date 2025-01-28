#include "DenoiseManager.h"
#include <hilog/log.h> // 鸿蒙日志库

bool DenoiseManager::loadModel(const std::string& modelPath) {
    HIAI_ModelInitParams initParams = {0};
    initParams.modelPath = modelPath.c_str();
    HIAI_Status status = HIAI_Model_Init(&initParams, &modelHandle);
    if (status != HIAI_SUCCESS) {
        HILOG_ERROR("[DenoiseManager]", "模型加载失败: %{public}s", modelPath.c_str());
        return false;
    }
    HILOG_INFO("[DenoiseManager]", "模型加载成功");
    return true;
}

bool DenoiseManager::denoiseImage(const cv::Mat& input, cv::Mat& output) {
    // 预处理：调整尺寸并归一化
    cv::Mat resizedInput;
    cv::resize(input, resizedInput, cv::Size(256, 256));
    cv::Mat inputBlob;
    resizedInput.convertTo(inputBlob, CV_32FC3, 1.0 / 255.0);

    // 创建 HiAI 输入张量
    HIAI_TensorBuffer inputTensor;
    inputTensor.data = inputBlob.data;
    inputTensor.size = inputBlob.total() * inputBlob.elemSize();
    inputTensor.dims[0] = 1;   // Batch size
    inputTensor.dims[1] = 256; // Height
    inputTensor.dims[2] = 256; // Width
    inputTensor.dims[3] = 3;   // Channels (RGB)

    // 执行推理
    HIAI_TensorBuffer outputTensor;
    HIAI_Status status = HIAI_Model_Run(modelHandle, &inputTensor, 1, &outputTensor, 1);
    if (status != HIAI_SUCCESS) {
        HILOG_ERROR("[DenoiseManager]", "推理失败");
        return false;
    }

    // 后处理：转换为图像格式
    cv::Mat outputBlob(cv::Size(256, 256), CV_32FC3, outputTensor.data);
    outputBlob.convertTo(output, CV_8UC3, 255.0);
    cv::cvtColor(output, output, cv::COLOR_RGB2BGR);
    return true;
}

double DenoiseManager::calculatePSNR(const cv::Mat& original, const cv::Mat& denoised) {
    cv::Mat diff;
    cv::absdiff(original, denoised, diff);
    diff.convertTo(diff, CV_32F);
    diff = diff.mul(diff);
    double mse = cv::mean(diff)[0];
    return 10.0 * log10((255.0 * 255.0) / (mse + 1e-10));
}

double DenoiseManager::calculateSSIM(const cv::Mat& original, const cv::Mat& denoised) {
    cv::Mat grayOriginal, grayDenoised;
    cv::cvtColor(original, grayOriginal, cv::COLOR_BGR2GRAY);
    cv::cvtColor(denoised, grayDenoised, cv::COLOR_BGR2GRAY);
    
    cv::Ptr<cv::quality::QualitySSIM> ssim = cv::quality::QualitySSIM::create(grayOriginal);
    cv::Mat scoreMat;
    cv::Scalar score = ssim->compute(grayDenoised, scoreMat);
    return score[0]; // SSIM 单通道值
}