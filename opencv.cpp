#include "opencv.h"

#define LabelFile "/home/eureka/Downloads/model_deploy/labels.txt"
#define ModelPath "/home/eureka/Downloads/model_deploy/model.onnx"

opencv::opencv(QObject *parent)
    : QObject{parent}
{
}

int opencv::run(QString img, opencv *signaler)
{
    Ort::Env env;
    Ort::RunOptions runOptions;
    Ort::Session session(nullptr);
    constexpr int64_t numChannels = 3;
    constexpr int64_t width = 128;
    constexpr int64_t height = 128;
    constexpr int64_t numClasses = 2; //分类的类别
    constexpr int64_t numInputElements = numChannels * width * height;

    //const string imageFile = "/home/eureka/Downloads/model_deploy/crack1.png";

    vector<string> labels = loadLabels(LabelFile);
    if (labels.empty()) {
        qDebug() << "Failed to load labels: " << LabelFile;
        return 1;
    }

    //load image
    const vector<float> imageVec = loadImage(img.toStdString());
    if (imageVec.empty()) {
        qDebug() << "Failed to load image: " << img;
        return 1;
    }

    if (imageVec.size() != numInputElements) {
        qDebug() << "Invalid image format. Must be 128 x 128 RGB image.";
        return 1;
    }

    // Use CPU
    session = Ort::Session(env, ModelPath, Ort::SessionOptions{ nullptr });

    // define shape
    const std::array<int64_t, 4> inputShape = { 1, numChannels, height, width };
    const std::array<int64_t, 2> outputShape = { 1, numClasses };

    // define array
    std::array<float, numInputElements> input;
    std::array<float, numClasses> results;

    // define Tensor
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
    auto inputTensor = Ort::Value::CreateTensor<float>(memory_info, input.data(), input.size(), inputShape.data(), inputShape.size());
    auto outputTensor = Ort::Value::CreateTensor<float>(memory_info, results.data(), results.size(), outputShape.data(), outputShape.size());

    // copy image data to input array
    std::copy(imageVec.begin(), imageVec.end(), input.begin());

    // define names
    Ort::AllocatorWithDefaultOptions ort_alloc;
    Ort::AllocatedStringPtr inputName = session.GetInputNameAllocated(0, ort_alloc);
    Ort::AllocatedStringPtr outputName = session.GetOutputNameAllocated(0, ort_alloc);
    const std::array<const char*, 1> inputNames = { inputName.get() };
    const std::array<const char*, 1> outputNames = { outputName.get() };
    inputName.release();
    outputName.release();

    // run inference
    try {
        session.Run(runOptions, inputNames.data(), &inputTensor, 1, outputNames.data(), &outputTensor, 1);
    }
    catch (Ort::Exception& e) {
        qDebug() << e.what();
        return 1;
    }

    // sort results
    std::vector<std::pair<size_t, float>> indexValuePairs;
    for (size_t i = 0; i < results.size(); ++i) {
        indexValuePairs.emplace_back(i, results[i]);
    }
    std::sort(indexValuePairs.begin(), indexValuePairs.end(), [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });

    if(indexValuePairs.size()>0)
        qDebug()<< "predict_label: "<< indexValuePairs[0].first << " , Score = " << indexValuePairs[0].second;
        signaler->ImgResult(img,indexValuePairs[0].first,indexValuePairs[0].second);
}

static std::vector<float> loadImage(const std::string& filename, int sizeX, int sizeY)
{
    cv::Mat image = cv::imread(filename);
    if (image.empty()) {
        std::cout << "No image found.";
    }
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    cv::resize(image, image, cv::Size(sizeX, sizeY));
    image = image.reshape(1, 1);
    std::vector<float> vec;
    image.convertTo(vec, CV_32FC1, 1. / 255);
    std::vector<float> output;
    for (size_t ch = 0; ch < 3; ++ch) {
        for (size_t i = ch; i < vec.size(); i += 3) {
            output.emplace_back(vec[i]);
        }
    }
    return output;
}

static std::vector<std::string> loadLabels(const std::string& filename)
{
    std::vector<std::string> output;

    std::ifstream file(filename);
    if (file) {
        std::string s;
        while (getline(file, s)) {
            output.emplace_back(s);
        }
        file.close();
    }

    return output;
}
