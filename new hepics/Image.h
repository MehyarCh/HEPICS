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

	Image(const Image &image) = delete;
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
	//Image load_image(char* path, int height ,int length ,int channels);



private:
	vector<float> data;
	static int IDcounter;
};

} // namespace hepics

/*class Image {
private:
    int w;
    int h;
    int c;
    float *data;
public:
    static int id;

    Image(int w, int h, int c);
    ~Image();
    float get_pixel(int x, int y, int c);
    void set_pixel(int x, int y, int c, float val);
    void add_pixel(int x, int y, int c, float val);
    void resize_image(int w, int h);
    static Image load_image_stb(char *filename, int channels);
    static Image load_image(char *filename, int w, int h, int c);
    static Image load_image_color(char *filename, int w, int h);



};*/

