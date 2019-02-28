#pragma once

#include <vector>
#include <cstddef>
#include <QImage>
#include <QString>


namespace hepics {

using std::vector;
using std::string;

class Image {
public:

	Image(size_t width, size_t height, size_t channels);

	Image(const Image &image) = default;
	Image(const Image &&image) = delete;
	const Image &operator=(const Image &image) = delete;
	const Image &operator=(const Image &&image) = delete;

	virtual ~Image() = default;


	const float &at(size_t x, size_t y, size_t c) const;
	float &at(size_t x, size_t y, size_t c);


	const size_t width;
	const size_t height;
	const size_t channels;
	const int id;

	void load_image(string path);
	const vector<float>& getData() const;
	void setData(const vector<float>& data);

	//Image load_image(char* path, int height ,int length ,int channels);


	vector<float> data;
	static int IDcounter;
};

} // namespace hepics
