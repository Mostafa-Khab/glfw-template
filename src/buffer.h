/*********************************
 * author     : mostafa khaled
 * date       : Sun Sep 15 02:50:54 AM EEST 2024
 * desc       : 
 ********************************/
#ifndef BUFFER_H
#define BUFFER_H

typedef struct buffer
{
  unsigned int id;
} buffer;

void buffer_create(buffer* b);
void buffer_bind(buffer b, unsigned int target);
void buffer_data(buffer, unsigned int target, unsigned int size, const void* data, unsigned int usage);
void buffer_delete(buffer* b);
void buffer_draw_arrays(buffer b, unsigned int mod, unsigned int first, unsigned int count);
//void buffer_draw_elements(buffer b, unsigned int prim, unsigned int start, unsigned int end);

#endif /* !BUFFER_HPP */
