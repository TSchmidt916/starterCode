#include "framebuffer.h"
#include "png++/png.hpp"

Framebuffer::Framebuffer()
    : width(100), height(100), fbStorage(width * height)
{
}

Framebuffer::Framebuffer(int w, int h)
    : width(w), height(h), fbStorage(width * height)
{
}

void Framebuffer::clearToColor( vec3 c )
{
    for (auto idx = 0u; idx < fbStorage.size(); ++idx)
    {
        fbStorage[idx] = c;
    }
}

void Framebuffer::clearToColor( vec3 c1, vec3 c2 )
{
    for (int j = 0; j < height; ++j)
    {
        float t = static_cast<float>(j) / static_cast<float>(height - 1);
        vec3 rowColor = c1 * (1.0f - t) + c2 * t;

        for (int i = 0; i < width; ++i)
        {
            fbStorage[j * width + i] = rowColor;
        }
    }
}

void Framebuffer::setPixelColor(int i, int j, vec3 c)
{
    if ( (i < 0) || (i >= width) || (j < 0) || (j >= height) )
    {
        return;
    }

    fbStorage[j * width + i] = c;
}

void Framebuffer::exportPNG(std::string filename)
{
    unsigned int w = static_cast<unsigned int>(width);
    unsigned int h = static_cast<unsigned int>(height);

    png::image< png::rgb_pixel > imData( w, h );

    for (unsigned int idx=0; idx<imData.get_height()*imData.get_width(); ++idx)
    {
        size_t x = idx % w;
        size_t y = static_cast<size_t>( floor(idx / static_cast<float>(imData.get_width())) );

        vec3 c = fbStorage[y * width + x];

        png::byte r = static_cast<png::byte>(c.x() * 255.0f);
        png::byte g = static_cast<png::byte>(c.y() * 255.0f);
        png::byte b = static_cast<png::byte>(c.z() * 255.0f);

        imData[h - 1 - y][x] = png::rgb_pixel( r, g, b );
    }
    imData.write( filename.c_str() );
}

