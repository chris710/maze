#include "main.h"


int main(int argc, char **argv) {
  unsigned int len;
  if (argc < 3) {
    printf("Usage: %s <width> <height>\n", *argv);
    return 1;
  }
  srand(time(NULL));

  /* You need to define this function in "maze.c" */
  maze *m = maze_random(atoi(argv[1]), atoi(argv[2]));
  //maze *m = maze_random(5, 5);
  /* And also this one, using the SVG drawing function provided in "svg.h" */
  maze_svg(m, "maze.svg");
  getch();
  return 0;
}


maze *maze_random(int width, int height) {
	/* open file with picture */
	FILE *picture;
	//picture = fopen_s(&picture, "picture.svg", "w");
	picture = fopen("picture.svg", "w");
	if (picture == NULL) {
		fprintf(stderr, "cannot create/open file\n");
		return NULL;
	}

	svg_header (picture, width, height);
	set_svg_color("gold");

	
	int i = 0, j = 0;		//iterators
	//maze fields initialisation
	maze new_maze = { height, width, (int**)malloc(sizeof(int*)*width) };
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
	for (i = 0; i < width; ++i) 
		for (j = 0; j < height; ++j)	
			new_maze.grid[i][j] = 0;
	
	//maze *labir = initialize_maze(width,height);		//maze we're working on
	//svg_rect (picture, 0, 0, labir->width, labir->height);
	svg_rect(picture, 0, 0, new_maze.width, new_maze.height);
	//create_outer_walls(picture, labir);
	divide(&new_maze, picture, 0, 0, width, height, choose_orientation(width,height));

	draw(&new_maze);

	svg_footer(picture);
	fclose(picture);
	return &new_maze;
}


void maze_svg(maze *maze, char *filename) {
	/* who needs it anyway*/
}

maze *initialize_maze(int width, int height) {
	int i = 0, j = 0;		//iterators

	//maze fields initialisation
	maze new_maze = { height, width, (int**)malloc(sizeof(int*)*width) };

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

	for (i = 0; i < width; ++i) 
		for (j = 0; j < height; ++j)	
			new_maze.grid[i][j] = 0;

	return &new_maze;
}

void create_outer_walls(FILE* f,maze* maz) {
	//maz->grid[0][]
	svg_rect (f, 0, 0, maz->width, maz->height);
}

enum orientation choose_orientation(int width, int height) {

	if (width > height) {
		return VERTICAL;	//vertical line
	}
	else if (height > width) {
		return HORIZONTAL;	//horizontal line
	}
	else
		return rand()%2 == 0 ? VERTICAL : HORIZONTAL;
}

void divide(maze *m, FILE * f, int x, int y, int width, int height, enum orientation o) {
	int i = 0;
	if (width < 2 || height < 2) return;	//if the rectangle is too small, return
	int is_horizontal = HORIZONTAL == o;

	/* wall source coords */
	int sx = x + (is_horizontal ? 0 : rand()%(width - 1) + 1);
	int sy = y + (is_horizontal ? rand()%(height - 1) +1 : 0);

	/* door coords */
	int dx = sx + (is_horizontal ? rand()%width : 0);
	int dy = sy + (is_horizontal ? 0 : rand()%height);

	/* draw 2 lines */
	int length = is_horizontal ? width : height;	//total wall length (doors included)
	//svg_line (f, sx , sy, dx - (is_horizontal?1:0), dy - (is_horizontal?0:1));
	svg_line (f, sx , sy, dx , dy );
	svg_line (f, dx + (is_horizontal?1:0), dy + (is_horizontal?0:1), sx + (is_horizontal?length:0), sy + (is_horizontal?0:length));

	/* draw it on the grid*/
	for (i = 0; i < length; ++i){
		m->grid[sx + (is_horizontal ? i : 0)][sy + (is_horizontal ? 0 : i)] = (is_horizontal ? 1 : 2);
	}
	m->grid[dx][dy] = 0;

	//////////* recursion */

	/* width and height of new rectangle */
	int w = is_horizontal ? width : (sx - x);
	int h = is_horizontal ? (sy - y) : height;
	/* first rectangle */
	divide(m, f, x, y, w, h, choose_orientation(w, h));
	/* source point for second rectangle */
	int x2 = is_horizontal ? x : (sx);
	int y2 = is_horizontal ? (sy) : y;
	/* width and height of new rectangle */
	w = is_horizontal ? width : (x + width - sx);
	h = is_horizontal ? (y + height - sy) : height;
	/* second rectangle */
	divide(m, f, x2, y2, w, h, choose_orientation(w, h));
}

void draw(maze *m) {
	int i, j;
	for (i = 0; i < m->width; ++i) {
		for (j = 0; j < m->height; ++j) {
			printf("%d ", m->grid[i][j]);
		}
		printf("\n");
	}
}