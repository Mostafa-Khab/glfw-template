/*********************************
 * author     : mostafa khaled
 * date       : Sun Sep 15 02:23:55 AM EEST 2024
 * desc       : 
 ********************************/
#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct texture
{
  unsigned int id;
} texture;

void texture_create(texture*);
void texture_bind(texture);
void texture_data(texture, int width, int height, int comps, const unsigned char* data);
void texture_filters(texture, int wrap, int min_mag);
void texture_delete(texture*);

#endif /* !TEXTURE_HPP */
