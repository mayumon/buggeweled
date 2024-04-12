#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

using namespace sf;

int tile = 32;
Vector2i offset(96,32);

struct bug{
    int x, y; // Window bug coordinates
    int col, row; // Grid bug coordinates
    int type; // Type of bug (integer 0-6)
    bool is_match;

    bug(){
        is_match = false;
    };
}

bug_grid[9][9]; // Grid of bugs

int main()
{
    // Open game window
    RenderWindow app(VideoMode(384,320), "buggeweled");
    app.setFramerateLimit(60);

    // Open texture files
    Texture t_bugs,t_board;

    t_board.loadFromFile("images/board.png");
    t_bugs.loadFromFile("images/bugs.png");

    Sprite board(t_board);
    Sprite bugs(t_bugs);

    // Initialize the grid with random bugs
    std::random_device rd;
    std::mt19937 gen(rd()); //
    std::uniform_int_distribution<> dis(1, 100);

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {

            bug_grid[i][j].x = j * tile;
            bug_grid[i][j].y = i * tile;

            bug_grid[i][j].row = i;
            bug_grid[i][j].col = j;

            int random_number = dis(gen);
            bug_grid[i][j].type = random_number % 7;
        }
    }

    // Game loop
    while (app.isOpen())
    {
        Event e{};

        while (app.pollEvent(e))
        {
            // Close window
            if (e.type == Event::Closed)
                app.close();
        }

        //TODO: bug movement (through mouse input)

        //TODO: match checking for matches of 4+ bugs

        // Match checking
        for(int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {

                // Vertical match
                if (bug_grid[i][j].type == bug_grid[i + 1][j].type &&
                bug_grid[i][j].type == bug_grid[i - 1][j].type) {

                    bug_grid[i - 1][j].is_match = true;
                    bug_grid[i][j].is_match = true;
                    bug_grid[i + 1][j].is_match = true;
                }

                // Horizontal match
                if (bug_grid[i][j].type == bug_grid[i][j + 1].type &&
                        bug_grid[i][j].type == bug_grid[i][j - 1].type){

                    bug_grid[i][j - 1].is_match = true;
                    bug_grid[i][j].is_match = true;
                    bug_grid[i][j + 1].is_match = true;
                }
            }
        }

        //TODO: update bug grid after match
        //TODO: bugs swap back if no match is found
        //TODO: bug animations (moving, matching, falling)
        //TODO: calculate and display score

        // Draw board and bugs
        app.draw(board);

        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {

                bug curr_bug = bug_grid[i][j];

                // Set bug sprite texture
                bugs.setTextureRect(IntRect(32 * curr_bug.type, 0, 32, 32));
                bugs.setPosition(curr_bug.x, curr_bug.y);
                bugs.move(offset.x - tile, offset.y - tile);

                app.draw(bugs);
            }
        }
        app.display();
    }
    return 0;
}