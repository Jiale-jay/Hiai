// Index.ets
import { DenoiseManager } from '../cpp/types/libentry'; // 导入声明的类

@Entry
@Component
struct DenoiseDemo {
  private denoiseManager: DenoiseManager = new DenoiseManager();

  build() {
    Button("执行去噪")
      .onClick(() => {
        const success = this.denoiseManager.loadModel("resources/rawfile/denoise.om");
        if (success) {
          this.denoiseManager.denoiseImage(
            "resources/base/media/noisy_image.jpg",
            "/data/storage/denoised.jpg"
          );
          const psnr = this.denoiseManager.calculatePSNR(
            "resources/base/media/noisy_image.jpg",
            "/data/storage/denoised.jpg"
          );
          console.log("PSNR Score: " + psnr.toFixed(2));
        }
      });
  }
}