#include "main.h"


int main(int argc, char **argv) {
  unsigned int len;
  if (argc < 3) {
    printf("Usage: %s <width> <height>\n", *argv);
    return 1;
  }

  /* You need to define this function in "maze.c" */
  maze *m = maze_random(atoi(argv[1]), atoi(argv[2]));

  /* And also this one, using the SVG drawing function provided in "svg.h" */
  maze_svg(m, "maze.svg");

  return 0;
}


maze *maze_random(int width, int height) {
	

}


void maze_svg(maze *maze, char *filename) {


}

maze *initialize_maze(int width, int height) {
	int i;
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
	}
	return &new_maze;
}
