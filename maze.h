typedef struct _node {
	int id;
	struct _node* left;
	struct _node* right;
}node;

typedef struct _tree  {
	node* root;
}tree;

typedef struct _maze {
	int height;
	int width;
	int** grid;
}maze;

maze *maze_random (int width, int height);
maze *initialize_maze(int width, int height);
void maze_svg (maze *maze, char *filename);

