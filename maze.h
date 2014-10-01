typedef struct _node {
	int id;
	struct _node* left;		//left child
	struct _node* right;	//right child
}node;

typedef struct _tree  {
	node* root;				//root node of a tree
}tree;

typedef struct _maze {
	int height;
	int width;
	int** grid;		//2d array for representation
}maze;

enum orientation {VERTICAL, HORIZONTAL};

maze *maze_random (int width, int height);									//create maze of given size
maze *initialize_maze(int width, int height);								//allocate memory for maze structure
void create_outer_walls(FILE* f, maze* maz);								//draw a rectangle in svg
void maze_svg (maze *maze, char *filename);									//draw a maze in svg
void divide(maze *m, FILE *f, int x, int y, int width, int height, enum orientation o);		//divide rectangle horizontaly or verticaly
enum orientation choose_orientation(int width, int height);					//choose vertical or horizontal line to draw

 