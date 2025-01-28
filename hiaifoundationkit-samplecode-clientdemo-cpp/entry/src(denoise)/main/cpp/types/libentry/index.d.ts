// index.d.ts

/** 去噪模型管理类 */
declare class DenoiseManager {
    /**
     * 加载去噪模型
     * @param modelPath 模型文件路径（如 `resources/rawfile/denoise.om`）
     * @returns 是否加载成功
     */
    loadModel(modelPath: string): boolean;
  
    /**
     * 执行图像去噪
     * @param inputImagePath 输入图像路径（如 `resources/base/media/noisy_image.jpg`）
     * @param outputImagePath 输出图像路径（如 `/data/storage/denoised.jpg`）
     * @returns 是否去噪成功
     */
    denoiseImage(inputImagePath: string, outputImagePath: string): boolean;
  
    /**
     * 计算 PSNR 分数
     * @param originalImagePath 原始图像路径
     * @param denoisedImagePath 去噪图像路径
     * @returns PSNR 分数（单位：dB）
     */
    calculatePSNR(originalImagePath: string, denoisedImagePath: string): number;
  
    /**
     * 计算 SSIM 分数
     * @param originalImagePath 原始图像路径
     * @param denoisedImagePath 去噪图像路径
     * @returns SSIM 分数（范围：0~1）
     */
    calculateSSIM(originalImagePath: string, denoisedImagePath: string): number;
  }
  
  // 导出 DenoiseManager 类
  export default DenoiseManager;