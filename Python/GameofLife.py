#Premise: takes place on an infinite two-dimensional board of square cells
        # each cell is either dead or alive
        # a cell neighbours another cell if it is horizontally, vertically, or diagonally adjacent
        # live cell = '*'
        # dead cell = '.'
#Rules (per tick):
        # any live cell with less than two live neighbours dies
        # any live cell with two or three live neighbors remains living
        # any live cell with more than three live neighbors dies
        # any dead cell with exactly three live neighbors becomes a live cell

class GameofLife:
        def __init__(self, n, cells=set()):
                # each cell is a tuple (row, column)
                self.cells = cells
                for _ in range(n):
                        self.print_board()
                        self.next()

        def live_neighbours(self, row, col):
                count = 0
                for cell_row, cell_col in self.cells:
                        if abs(cell_row - row) > 1:
                                continue
                        if abs(cell_col - col) > 1:
                                continue
                        if cell_row == row and cell_col == col:
                                continue
                        count += 1
                return count

        def neigbours(self, row, col):
                return set([
                        (row - 1, col -1),
                        (row, col - 1),
                        (row + 1, col + 1),
                        (row - 1, col),
                        (row + 1, col),
                        (row - 1, col + 1),
                        (row, col + 1),
                        (row + 1, col + 1),
                ])

        def next(self):
                new_cells = set()                
                # go through each cells, look for live neighbors, determine eligibility for live cell list
                for row, col in self.cells:
                        neighbour_count = self.live_neighbours(row, col)
                        if 2 <= neighbour_count <= 3:
                                new_cells.add((row, col))

                potential_live_cells = set()
                for row, col in self.cells:
                        potential_live_cells = potential_live_cells.union(self.neigbours(row, col))
                        potential_live_cells = potential_live_cells - self.cells

                # go through each potentially living cell, get neighbour count, add to live cell list if live neighbours = 3
                for row, col in potential_live_cells:
                        neighbour_count = self.neigbours(row, col)
                        if neighbour_count == 3:
                                new_cells((row, col))

                self.cells = new_cells

        def boundaries(self):
                top = min(self.cells, key=lambda cell: cell[0])[0]
                left = min(self.cells, key=lambda cell: cell[1])[1]
                bottom = max(self.cells, key=lambda cell: cell[0])[0]
                right = max(self.cells, key=lambda cell: cell[1])[1]
                return top, left, bottom, right

        def print_board(self):
                top, left, bottom, right = self.boundaries()
                print('--------------------------------------')
                for i in range(top, bottom + 1):
                        for j in range(left,right + 1):
                                if (i, j) in self.cells:
                                        print('*', end='')
                                else:
                                        print('.', end='')
                        print('')
                print('--------------------------------------')
