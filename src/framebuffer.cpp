#include "framebuffer.h"
#include "png++/png.hpp"

Framebuffer::Framebuffer()
    : m_width(100), m_height(100), fbStorage(m_width * m_height)
{
}

Framebuffer::Framebuffer(int w, int h)
    : m_width(w), m_height(h), fbStorage(m_width * m_height)
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
    for (int j = 0; j < m_height; ++j)
    {
        float t = static_cast<float>(j) / static_cast<float>(m_height - 1);
        vec3 rowColor = c1 * (1.0f - t) + c2 * t;

        for (int i = 0; i < m_width; ++i)
        {
            fbStorage[j * m_width + i] = rowColor;
        }
    }
}

void Framebuffer::setPixelColor(int i, int j, vec3 c)
{
    if ( (i < 0) || (i >= m_width) || (j < 0) || (j >= m_height) )
    {
        return;
    }

    fbStorage[j * m_width + i] = c;
}

void Framebuffer::exportPNG(std::string filename)
{
    unsigned int w = static_cast<unsigned int>(m_width);
    unsigned int h = static_cast<unsigned int>(m_height);

    png::image< png::rgb_pixel > imData( w, h );

    for (unsigned int idx=0; idx<imData.get_height()*imData.get_width(); ++idx)
    {
        size_t x = idx % w;
        size_t y = static_cast<size_t>( floor(idx / static_cast<float>(imData.get_width())) );

        vec3 c = fbStorage[y * m_width + x];

        png::byte r = static_cast<png::byte>(c.x() * 255.0f);
        png::byte g = static_cast<png::byte>(c.y() * 255.0f);
        png::byte b = static_cast<png::byte>(c.z() * 255.0f);

        imData[h - 1 - y][x] = png::rgb_pixel( r, g, b );
    }
    imData.write( filename.c_str() );
}

