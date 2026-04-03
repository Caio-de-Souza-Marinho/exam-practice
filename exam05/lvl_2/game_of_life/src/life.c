#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	read_input(char *board, int width, int height);
void	print_board(char *board, int width, int height);
void	simulate(char *board, char *next, int width, int height);

int	main(int argc, char **argv)
{
	(void)argc;
	int	width = atoi(argv[1]);
	int	height = atoi(argv[2]);
	int	iterations = atoi(argv[3]);
	char	*board = calloc(width * height, sizeof(char));
	char	*next = calloc(width *height, sizeof(char));

	read_input(board, width, height);

	char	*temp;
	while (iterations > 0)
	{
		simulate(board, next, width, height);
		temp = board;
		board = next;
		next = temp;
		iterations--;
	}
	print_board(board, width, height);

	free(board);
	free(next);

	return (0);

}

void	read_input(char *board, int width, int height)
{
	int	col = 0;
	int	row = 0;
	int	pen_down = 0;
	char	c;

	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		if (c == 'x')
		{
			pen_down = !pen_down;
			board[row * width + col] = pen_down ? 1 : board[row * width + col];
		}
		else if (c == 'w' && row > 0)
			row--;
		else if (c == 's' && row < height - 1)
			row++;
		else if (c == 'a' && col > 0)
			col--;
		else if (c == 'd' && col < width - 1)
			col++;

		if (pen_down && c != 'x')
			board[row * width + col] = 1;
	}
}

void	print_board(char *board, int width, int height)
{
	int	row = 0;
	int	col;

	while (row < height)
	{
		col = 0;
		while (col < width)
		{
			putchar(board[row * width + col] ? '0' : ' ');
			col++;
		}
		putchar('\n');
		row++;
	}
}

void	simulate(char *board, char *next, int width, int height)
{
	int	row = 0;
	int	col;
	int	neighbors;
	int	dr;
	int	dc;

	while (row < height)
	{
		col = 0;
		while (col < width)
		{
			neighbors = 0;
			dr = -1;
			while (dr <= 1)
			{
				dc = -1;
				while (dc <= 1)
				{
					if (dr == 0 && dc == 0)
					{
						dc++;
						continue;
					}
					if (row + dr >= 0 && row + dr < height &&
	 					col + dc >= 0 && col + dc < width)
						neighbors += board[(row + dr) * width + (col + dc)];
					dc++;
				}
				dr++;
			}
			if (board[row * width + col] == 1)
				next[row * width + col] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
			else
				next[row * width + col] = (neighbors == 3) ? 1 : 0;
			col++;
		}
		row++;
	}
}
