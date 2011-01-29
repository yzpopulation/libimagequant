/**
 ** Copyright (C) 1989, 1991 by Jef Poskanzer.
 ** Copyright (C) 1997, 2000, 2002 by Greg Roelofs; based on an idea by
 **                                Stefan Schneider.
 ** Copyright (C) 2009 by Kornel Lesinski.
 **
 ** Permission to use, copy, modify, and distribute this software and its
 ** documentation for any purpose and without fee is hereby granted, provided
 ** that the above copyright notice appear in all copies and that both that
 ** copyright notice and this permission notice appear in supporting
 ** documentation.  This software is provided "as is" without express or
 ** implied warranty.
 */

#include <math.h>

/* from pam.h */

typedef struct {
    unsigned char r, g, b, a;
} rgb_pixel;

typedef struct {
    float r, g, b, a;
} f_pixel;

inline static f_pixel to_f(rgb_pixel r)
{
    return (f_pixel){r.r/255.0,r.g/255.0,r.b/255.0,r.a/255.0};
}

inline static rgb_pixel to_rgb(f_pixel px)
{
    return (rgb_pixel){
        px.r>=1.0 ? 255 : (px.r<0 ? 0 : px.r*256.0),
        px.g>=1.0 ? 255 : (px.g<0 ? 0 : px.g*256.0),
        px.b>=1.0 ? 255 : (px.b<0 ? 0 : px.b*256.0),
        px.a>=1.0 ? 255 : (px.a<0 ? 0 : px.a*256.0),
    };
}

/*
 typedef struct {
 ush r, g, b, a;
 } apixel16;
 */

/* from pamcmap.h */

typedef struct acolorhist_item *acolorhist_vector;
struct acolorhist_item {
    f_pixel acolor;
    int value;
    /*    int contrast;*/
};

typedef struct acolorhist_list_item *acolorhist_list;
struct acolorhist_list_item {
    acolorhist_list next;
    struct acolorhist_item ch;
};

typedef acolorhist_list *acolorhash_table;


typedef unsigned char pixval; /* GRR: hardcoded for now; later add 16-bit support */


acolorhist_vector pam_computeacolorhist(rgb_pixel*const* apixels, int cols, int rows, int maxacolors, int ignorebits, int* acolorsP);
void pam_freeacolorhist(acolorhist_vector achv);