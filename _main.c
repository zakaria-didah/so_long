
// #include <mlx.h>
// #include <png.h>
// #include <stdlib.h>
// #include <stdio.h>

// typedef struct s_image {
//     void    *img_ptr;
//     int     *data;
//     int     width;
//     int     height;
//     int     bpp;
//     int     size_line;
//     int     endian;
// }   t_image;

// int png_to_mlx_image(void *mlx_ptr, char *filename, t_image *img)
// {
//     FILE *fp = fopen(filename, "rb");
//     if (!fp) {
//         perror("File opening error");
//         return 1;
//     }

//     png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//     if (!png) {
//         fclose(fp);
//         return 1;
//     }

//     png_infop info = png_create_info_struct(png);
//     if (!info) {
//         png_destroy_read_struct(&png, NULL, NULL);
//         fclose(fp);
//         return 1;
//     }

//     if (setjmp(png_jmpbuf(png))) {
//         png_destroy_read_struct(&png, &info, NULL);
//         fclose(fp);
//         return 1;
//     }

//     png_init_io(png, fp);
//     png_read_info(png, info);

//     img->width = png_get_image_width(png, info);
//     img->height = png_get_image_height(png, info);
//     int color_type = png_get_color_type(png, info);
//     int bit_depth = png_get_bit_depth(png, info);

//     png_read_update_info(png, info);

//     // Prepare image to pass to MiniLibX
//     img->img_ptr = mlx_new_image(mlx_ptr, img->width, img->height);
//     img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);

//     png_bytep row = (png_bytep) malloc(3 * img->width * sizeof(png_byte));

//     for (int y = 0; y < img->height; y++) {
//         png_read_row(png, row, NULL);
//         for (int x = 0; x < img->width; x++) {
//             png_byte red = row[x * 3];
//             png_byte green = row[x * 3 + 1];
//             png_byte blue = row[x * 3 + 2];
//             int color = (red << 16) | (green << 8) | blue;
//             img->data[y * img->width + x] = color;
//         }
//     }

//     free(row);
//     png_destroy_read_struct(&png, &info, NULL);
//     fclose(fp);

//     return 0;
// }



// int	main(void)
// {
//     void	*mlx;
//     void	*win;
//     t_image img;

//     mlx = mlx_init();
//     win = mlx_new_window(mlx, 1080, 720, "Hello world!");
//     png_to_mlx_image(mlx, "/home/zdidah/workspace/solong/textures/2D Pixel Dungeon Asset Pack/Dungeon_Tileset_at.png", &img);
//     mlx_put_image_to_window(mlx, win, img.img_ptr, 0, 0);
//     mlx_hook(win, 17, 0, _close, mlx);
//     mlx_loop(mlx);
//     return (0);
// }


// #include "mlx.h"
// #include "lodepng.h"
// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_image {
//     unsigned char *pixels;
//     unsigned int width;
//     unsigned int height;
// } t_image;

// int load_png(const char *filename, t_image *image) {
//     unsigned error = lodepng_decode32_file(&image->pixels, &image->width, &image->height, filename);
//     if (error) {
//         printf("Error %u: %s\n", error, lodepng_error_text(error));
//         return 0;
//     }
//     return 1;
// }

// void blend_images(t_image *background, t_image *foreground, int pos_x, int pos_y) {
//     for (unsigned int y = 0; y < foreground->height; y++) {
//         for (unsigned int x = 0; x < foreground->width; x++) {
//             int fg_index = (y * foreground->width + x) * 4; // Foreground pixel index
//             int bg_index = ((pos_y + y) * background->width + (pos_x + x)) * 4; // Background pixel index

//             unsigned char fg_r = foreground->pixels[fg_index];
//             unsigned char fg_g = foreground->pixels[fg_index + 1];
//             unsigned char fg_b = foreground->pixels[fg_index + 2];
//             unsigned char fg_a = foreground->pixels[fg_index + 3]; // Alpha channel

//             unsigned char bg_r = background->pixels[bg_index];
//             unsigned char bg_g = background->pixels[bg_index + 1];
//             unsigned char bg_b = background->pixels[bg_index + 2];

//             // Blend the colors using the alpha channel
//             background->pixels[bg_index] = (fg_r * fg_a + bg_r * (255 - fg_a)) / 255;
//             background->pixels[bg_index + 1] = (fg_g * fg_a + bg_g * (255 - fg_a)) / 255;
//             background->pixels[bg_index + 2] = (fg_b * fg_a + bg_b * (255 - fg_a)) / 255;
//         }
//     }
// }

// void render_image(void *mlx, void *win, t_image *image) {
//     void *mlx_image = mlx_new_image(mlx, image->width, image->height);
//     char *mlx_data = mlx_get_data_addr(mlx_image, &(int){0}, &(int){0}, &(int){0});

//     for (unsigned int y = 0; y < image->height; y++) {
//         for (unsigned int x = 0; x < image->width; x++) {
//             int index = (y * image->width + x) * 4;
//             int mlx_index = y * image->width + x;
//             int color = (image->pixels[index] << 16) | (image->pixels[index + 1] << 8) | image->pixels[index + 2];
//             ((int *)mlx_data)[mlx_index] = color;
//         }
//     }

//     mlx_put_image_to_window(mlx, win, mlx_image, 0, 0);
//     mlx_destroy_image(mlx, mlx_image);
// }
// int main() {
//     void *mlx = mlx_init();
//     void *win = mlx_new_window(mlx, 800, 600, "Transparency Example");

//     t_image background, foreground;

//     // Load the background image
//     if (!load_png("/home/zdidah/workspace/solong/textures/2D Pixel Dungeon Asset Pack/Dungeon_Tileset_at.png", &background)) {
//         return 1;
//     }

//     // Load the foreground image
//     if (!load_png("/home/zdidah/workspace/solong/lets_play_btn.png", &foreground)) {
//         free(background.pixels);
//         return 1;
//     }

//     // Blend the foreground image onto the background image
//     blend_images(&background, &foreground, 100, 100); // Position the foreground at (100, 100)

//     // Render the blended image
//     render_image(mlx, win, &background);

//     // Free memory
//     free(background.pixels);
//     free(foreground.pixels);

//     mlx_loop(mlx);
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

typedef struct s_win {
    void	*mlx_ptr;
    void	*win_ptr;
}	t_win;

typedef struct s_img {
    void	*img_ptr;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
    int		w;
    int		h;
    t_win	win;
}	t_img;


void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h) {
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y) {
	return (*(unsigned int *)((img.addr + (y * img.line_len) + (x * img.bpp / 8))));
}

void	put_img_to_img(t_img dst, t_img src, int x, int y) {
	int i;
	int j;

	i = 0;
	while(i < src.w) {
		j = 0;
		while (j < src.h) {
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

int main(void)
{
 	t_win	tutorial;
	t_img	base_image;
	t_img	bg;
	t_img	ring;

	// signal(SIGINT, sig_handler);
    tutorial.mlx_ptr = mlx_init();
	tutorial.win_ptr = mlx_new_window( tutorial.mlx_ptr, 1000, 650, "transparency");

	base_image.img_ptr = mlx_new_image(tutorial.mlx_ptr, 1000, 650 );
    base_image.addr = mlx_get_data_addr(base_image.img_ptr, &base_image.bpp, &base_image.line_len, &base_image.endian);

	{
		bg.img_ptr = mlx_xpm_file_to_image(tutorial.mlx_ptr ,"/home/zdidah/workspace/solong/textures/sample_640×426.xpm", &bg.w, &bg.h);
		bg.addr = mlx_get_data_addr(bg.img_ptr, &bg.bpp, &bg.line_len, &bg.endian);
        if (!bg.img_ptr)
			return (2);
		put_img_to_img(base_image, bg, 0, 0);
	}
	{
		ring.img_ptr = mlx_xpm_file_to_image(tutorial.mlx_ptr ,"/home/zdidah/workspace/solong/textures/Prototype_Character.xpm", &ring.w, &ring.h);
		ring.addr = mlx_get_data_addr(ring.img_ptr, &ring.bpp, &ring.line_len, &ring.endian);
        if (!ring.img_ptr)
			return (2);
		put_img_to_img(base_image, ring, 50, 100);
	}
	mlx_put_image_to_window (tutorial.mlx_ptr, tutorial.win_ptr, base_image.img_ptr, 0, 0);
	mlx_loop(tutorial.mlx_ptr);
	//mlx_destroy_window(tutorial.mlx_ptr, tutorial.win_ptr);
	return (0);
}