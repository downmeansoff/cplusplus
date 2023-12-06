#include <iostream>
#include <stdexcept>
#include <random>

class GrayscaleImage {
private:
    int width;
    int height;
    bool randomFill;
    char* data;

public:
    GrayscaleImage(int w, int h, bool random = true) : width(w), height(h), randomFill(random) {
        size_t size = static_cast<size_t>(width) * height;
        data = new char[size];
        if (randomFill) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, std::numeric_limits<char>::max());
            for (size_t i = 0; i < size; ++i) {
                data[i] = static_cast<char>(dist(gen));
            }
        }
        else {
            memset(data, 0, size * sizeof(char));
        }
    }

    ~GrayscaleImage() {
        delete[] data;
    }

    char& operator()(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Invalid indices");
        }
        return data[y * width + x];
    }

    GrayscaleImage operator*(const GrayscaleImage& other) const {
        GrayscaleImage result(width, height, false);
        for (int i = 0; i < width * height; ++i) {
            result.data[i] = static_cast<char>(data[i] & other.data[i]);
        }
        return result;
    }

    GrayscaleImage operator+(const GrayscaleImage& other) const {
        GrayscaleImage result(width, height, false);
        for (int i = 0; i < width * height; ++i) {
            result.data[i] = static_cast<char>(data[i] | other.data[i]);
        }
        return result;
    }

    GrayscaleImage operator*(char constant) const {
        GrayscaleImage result(width, height, false);
        for (int i = 0; i < width * height; ++i) {
            result.data[i] = static_cast<char>(data[i] * constant);
        }
        return result;
    }

    GrayscaleImage operator+(char constant) const {
        GrayscaleImage result(width, height, false);
        for (int i = 0; i < width * height; ++i) {
            result.data[i] = static_cast<char>(data[i] + constant);
        }
        return result;
    }

    GrayscaleImage operator!() const {
        GrayscaleImage result(width, height, false);
        for (int i = 0; i < width * height; ++i) {
            result.data[i] = static_cast<char>(std::numeric_limits<char>::max() - data[i]);
        }
        return result;
    }

    double fillRatio() const {
        int sum = 0;
        for (int i = 0; i < width * height; ++i) {
            sum += static_cast<int>(data[i]);
        }
        return static_cast<double>(sum) / (width * height * std::numeric_limits<char>::max());
    }

    bool operator==(const GrayscaleImage& other) const {
        if (width != other.width || height != other.height) {
            return false;
        }
        return std::equal(data, data + width * height, other.data);
    }

    bool operator!=(const GrayscaleImage& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const GrayscaleImage& image) {
        for (int y = 0; y < image.height; ++y) {
            for (int x = 0; x < image.width; ++x) {
                os << static_cast<int>(image.data[y * image.width + x]) << ' ';
            }
            os << '\n';
        }
        return os;
    }
};
