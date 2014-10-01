#include "main.h"


int main(int argc, char **argv) {
  unsigned int len;
  /*if (argc < 3) {
    printf("Usage: %s <width> <height>\n", *argv);
    return 1;
  }*/

  /* You need to define this function in "maze.c" */
  //maze *m = maze_random(atoi(argv[1]), atoi(argv[2]));
  maze *m = maze_random(5, 5);
  srand(time(NULL));

  /* And also this one, using the SVG drawing function provided in "svg.h" */
  maze_svg(m, "maze.svg");

  return 0;
}


maze *maze_random(int width, int height) {
	/* open file with picture */
	FILE *picture;
	//picture = fopen_s(&picture, "picture.svg", "w");
	picture = fopen("picture.svg", "w");
	if (picture = NULL) {
		fprintf(stderr, "cannot create/open file\n");
		return NULL;
	}

	svg_header (picture, width, height);
	//void set_svg_color(char *color);

	maze *labir = initialize_maze(width,height);		//maze we're working on
	create_outer_walls(picture, labir, width, height);
	divide(picture, 0, 0, width, height, 0,choose_orientation(width,height));

	//fprintf(picture, "dupadupa");

	svg_footer(picture);
	fclose(picture);
	return labir;
}


void maze_svg(maze *maze, char *filename) {
	/* who needs it anyway*/
}

maze *initialize_maze(int width, int height) {
	int i = 0, j = 0;
	maze new_maze;
	new_maze.height = height;
	new_maze.width = width;
	new_maze.grid = (int**)malloc(sizeof(int*)*width);

	if (new_maze.grid == NULL) {	//check if allocation succeeded
		fprintf(stderr, "cannot allocate grid\n");
		return NULL;
	}

	for (i = 0; i < width; ++i) {	//fill in the grid
		new_maze.grid[i] = (int*)malloc(height*sizeof(int));
		if (new_maze.grid[i] == NULL) {		//check if allocation succeeded
			fprintf(stderr, "cannot allocate row\n");
			return NULL;
		}
		for (j = 0; j < height; ++j)	//fill maze with emptiness
			new_maze.grid[i][j] = 0;
	}
	return &new_maze;
}

void create_outer_walls(FILE* f,maze* maz, int width, int height) {
	//maz->grid[0][]
	//svg_rect (f, 0, 0, 0, height);
	svg_rect (f, 0, 0, width, height);
	//svg_rect (f, width, 0,  width, height);
	//svg_rect (f, 0, height, width, height);
	
}

enum orientation choose_orientation(int width, int height) {

	if (width > height) {
		return VERTICAL;	//vertical line
	}
	else if (height>width) {
		return HORIZONTAL;	//horizontal line
	}
	else
		return rand(2) == 0 ? VERTICAL : HORIZONTAL;
}

void divide(maze *m, FILE * f, int x, int y, int width, int height, enum orientation o) {
	int i = 0;
	if (width < 2 || height < 2) return;
	int is_horizontal = HORIZONTAL == o;

	/* wall source coords */
	int sx = x + is_horizontal ? 0 : rand(width - 2);
	int sy = y + is_horizontal ? rand(height - 2) : 0;

	/* door coords */
	int dx = sx + (is_horizontal ? rand(width) : 0);
	int dy = sy + (is_horizontal ? 0 : rand(height));

	int length = is_horizontal ? width : height;

	/* draw 2 lines */
	svg_line (f, sx , sy, dx-is_horizontal?1:0, dy-is_horizontal?0:1);
	svg_line (f, dx-is_horizontal?1:0, dy-is_horizontal?0:1, sx+is_horizontal?length:0, sy+is_horizontal?0:length);

	/* draw it on the grid*/
	for (i = 0; i < length; ++i){
		m->grid[sx + is_horizontal?i:0][sy + is_horizontal?0:i] = 1; // [is_horizontal ? sy : sx][is_horizontal ? sy : sx]
	}

	//////////* recursion */

	/* width and height of new rectangle */
	int w = is_horizontal ? width : (sx - x + 1);
	int h = is_horizontal ? (sy - y + 1) : height;
	divide(m->grid, f, x, y, w, h, choose_orientation(w, h));

	int x2 = is_horizontal ? x : (sx + 1);
	int y2 = is_horizontal ? (sy + 1) : y;
	w = is_horizontal ? width : (x + width - sx - 1);
	h = is_horizontal ? (y + height - sy - 1) : height;
	divide(m->grid, f, x2, y2, w, h, choose_orientation(w, h));
}