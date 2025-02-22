import random
import sys
from collections import deque

def is_valid_map(grid):
    """Checks if all coins are reachable from the player's position using BFS."""
    rows, cols = len(grid), len(grid[0])
    visited = [[False] * cols for _ in range(rows)]
    
    # Find the player's starting position
    player_pos = None
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 'P':
                player_pos = (r, c)
                break
        if player_pos:
            break

    if not player_pos:
        return False  # No player position found
    
    # Perform BFS from the player's position
    queue = deque([player_pos])
    visited[player_pos[0]][player_pos[1]] = True
    
    while queue:
        x, y = queue.popleft()
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and not visited[nx][ny] and grid[nx][ny] != '1':
                visited[nx][ny] = True
                queue.append((nx, ny))
    
    # Check if all coins are reachable
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 'C' and not visited[r][c]:
                return False
    return True

def generate_map(rows, cols, validity):
    """Generates a random map based on the specified validity."""
    if rows < 3 or cols < 3:
        raise ValueError("Map must be at least 3x3 in size.")
    
    # Initialize the map with walls
    grid = [['1'] * cols for _ in range(rows)]
    
    # Create the inner area with walkable spaces
    for r in range(1, rows - 1):
        for c in range(1, cols - 1):
            grid[r][c] = '0'
    
    # Place the player at a random position
    px, py = random.randint(1, rows - 2), random.randint(1, cols - 2)
    grid[px][py] = 'P'
    
    # Place the exit door at a random position (not the player's position)
    while True:
        ex, ey = random.randint(1, rows - 2), random.randint(1, cols - 2)
        if (ex, ey) != (px, py):
            grid[ex][ey] = 'E'
            break
    
    # Randomly place walls inside the map
    for _ in range((rows * cols) // 10):  # Adjust density as needed
        rx, ry = random.randint(1, rows - 2), random.randint(1, cols - 2)
        if grid[rx][ry] == '0':  # Place walls only in empty spaces
            grid[rx][ry] = '1'
    
    # Randomly place coins
    for _ in range(random.randint(1, (rows * cols) // 10)):
        while True:
            cx, cy = random.randint(1, rows - 2), random.randint(1, cols - 2)
            if grid[cx][cy] == '0':  # Only place a coin on an empty space
                grid[cx][cy] = 'C'
                break
    
    if validity == "INVALID":
        # Place an unreachable coin by surrounding it with walls
        while True:
            cx, cy = random.randint(1, rows - 2), random.randint(1, cols - 2)
            if grid[cx][cy] == '0':
                grid[cx][cy] = 'C'
                for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    nx, ny = cx + dx, cy + dy
                    if 1 <= nx < rows - 1 and 1 <= ny < cols - 1:
                        grid[nx][ny] = '1'
                break
    else:
        # Ensure map is valid
        while not is_valid_map(grid):
            grid = generate_map(rows, cols, "VALID")
    
    return grid

def print_map(grid):
    """Prints the map to the console."""
    for row in grid:
        print(''.join(row))

if __name__ == "__main__":
    # Parse command-line arguments
    if len(sys.argv) != 4 or sys.argv[1] not in ["VALID", "INVALID"]:
        print("Usage: python3 map.py [VALID|INVALID] rows cols")
        sys.exit(1)
    
    validity = sys.argv[1]
    rows, cols = int(sys.argv[2]), int(sys.argv[3])
    
    generated_map = generate_map(rows, cols, validity)
    print_map(generated_map)
