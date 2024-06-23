#include "RenderWindow.h"

Game::Game(const char* title)
    : window(nullptr), renderer(nullptr), tileSize(16), gravity(10), is_left(false), is_right(false), is_up(false), is_down(false)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Failed to initialize SDL! " << SDL_GetError() << std::endl;
        exit(1);
    }
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
    {
        std::cerr << "PNG OR JPG Initialization has Failed! " << SDL_GetError() << std::endl;
        exit(1);
    }
    if (TTF_Init() == -1)
    {
        std::cerr << "Failed to load font! " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_DisplayMode display;
    if (SDL_GetDesktopDisplayMode(0, &display) != 0)
    {
        std::cerr << "No Display Found! " << SDL_GetError() << std::endl;
        exit(1);
    }
    windowWidth = display.w - 120;
    windowHeight = display.h - 110;
    SDL_CreateWindowAndRenderer(windowWidth, windowHeight, SDL_WINDOW_RESIZABLE , &window, &renderer);
    SDL_SetWindowTitle(window, title);
    /*window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display.w - 260 , display.h - 120 , SDL_WINDOW_SHOWN ) ;
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED ) ;*/
    if (window == nullptr || renderer == nullptr)
    {
        std::cerr << "Window and Render unable to setup properly. " << SDL_GetError() << std::endl;
        exit(1);
    }
    font = TTF_OpenFont("res/Font.ttf", 24);
    player.setTexture("res/player.png", renderer);
    player.setSource(0, 0, 24, 32);
    player.setDest(windowWidth / 2, windowHeight / 2, 24, 32);
    idle_r = player.createCycle(1, 24, 32, 2, 20);
    idle_l = player.createCycle(2, 24, 32, 2, 20);
    run_r = player.createCycle(3, 24, 32, 5, 4);
    run_l = player.createCycle(4, 24, 32, 5, 4);
    player.setCurrentAnimation(idle_r);
    //audioEffect.load("res/wavAudio.wav");
    loadMap("res/1.level");
    mapX = mapY = 0;
    speed = 5;
    gameRunning = true;
    frameCount = lastFrame = timerFPS = 0;
    startGame();
}

void Game::inputs()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if ((event.type == SDL_QUIT) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)))
            gameRunning = false;
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_w)
            {
                is_up = 1;
            }
            if (event.key.keysym.sym == SDLK_s)
            {
                is_down = 1;
            }
            if (event.key.keysym.sym == SDLK_a)
            {
                is_left = 1;
                is_right = 0;
            }
            if (event.key.keysym.sym == SDLK_d)
            {
                is_right = 1;
                is_left = 0;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_w)
            {
                is_up = 0;
                //player.setCurrentAnimation( ) ;
            }
            if (event.key.keysym.sym == SDLK_s)
                is_down = 0;
            if (event.key.keysym.sym == SDLK_a)
            {
                is_left = 0;
                player.setCurrentAnimation(idle_l);
            }
            if (event.key.keysym.sym == SDLK_d)
            {
                is_right = 0;
                player.setCurrentAnimation(idle_r);
            }
        }
        else if ( event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED )
        {
            windowWidth = event.window.data1;
            windowHeight = event.window.data2;
            SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);
        }
        SDL_GetMouseState(&mouseX, &mouseY);
    }
}

void Game::startGame()
{
    static int lastTime = 0;
    while (isRunning())
    {
        lastFrame = SDL_GetTicks();
        if (lastFrame >= (lastTime + 1000))
        {
            lastTime = lastFrame ;
            frameCount = 0;
            //count++ ;
        }
        //std::cout << mouseX << " , " << mouseY << std::endl ;
        render();
        inputs();
        update();

        //if (count >= 3) gameRunning = false ;
    }
}

void Game::update()
{
    if (is_left)
    {
        if (player.getCurrentAnimation() != run_l)
        {
            player.setCurrentAnimation(run_l);
        }
        player.setDest(player.getDX() - speed, player.getDY());
    }
    if (is_right) {
        if (player.getCurrentAnimation() != run_r)
        {
            player.setCurrentAnimation(run_r);
        }
        player.setDest(player.getDX() + speed, player.getDY());
    }

    player.updateAnimation();

    fall = true;
    for (int i = 0; i < map.size(); i++) {
        if (collision(player, map[i])) {
            if (map[i].getSolid())
                fall = false;
            // Elevator Block
            if (map[i].getId() == 35)
            {
                if (is_up) {
                    player.setDest(player.getDX(), player.getDY() - (10 * tileSize));
                    is_up = is_down = 0;
                }
                if (is_down) {
                    player.setDest(player.getDX(), player.getDY() + (10 * tileSize));
                    is_up = is_down = 0;
                }
            }
        }
    }

    if (fall)
        player.setDest(player.getDX(), player.getDY() + gravity);

    if (player.getDX() < 100)
    {
        player.setDest(100, player.getDY()); scroll(speed, 0);
    }
    if (player.getDX() > windowWidth - 100)
    {
        player.setDest(windowWidth - 100, player.getDY());
        scroll(-speed, 0);
    }
    if (player.getDY() < 100)
    {
        player.setDest(player.getDX(), 100);
        scroll(0, speed);
    }
    if (player.getDY() > windowHeight - 100)
    {
        player.setDest(player.getDX(), windowHeight - 100);
        scroll(0, -speed);
    }

}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 126, 192, 238, 255);
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = windowWidth;
    rect.h = windowHeight;
    SDL_RenderFillRect(renderer, &rect);

    drawMap();
    drawObject(player);

    frameCount++;
    timerFPS = SDL_GetTicks() - lastFrame ;
    if (timerFPS < ( 1000 / 60) )
        SDL_Delay( ( 1000 / 60 ) - timerFPS ) ;

    SDL_RenderPresent(renderer);
}

void Game::drawObject( Object ob )
{
	SDL_Rect src = ob.getSource() ;
	SDL_Rect dest = ob.getDest() ;

	SDL_RenderCopyEx(renderer, ob.getTexture(), &src, &dest , 0 , nullptr , SDL_FLIP_NONE ) ;
}

void Game::drawFont(const char* msg, int x, int y, int r, int g, int b) // Can ad size also.
{
    SDL_Surface* surf;
    SDL_Texture* text;
    SDL_Color color;
    color.r = r; color.g = g; color.b = b;
    color.a = 255; // Set Transparency to completely solid

    SDL_Rect rect;
    surf = TTF_RenderText_Solid(font, msg, color);
    text = SDL_CreateTextureFromSurface(renderer, surf);
    if (font == nullptr || surf == nullptr || text == nullptr)
    {
        std::cerr << "Unable to process Sans.ttf function! " << TTF_GetError() << std::endl;
        exit(1);
    }
    rect.x = x;
    rect.y = y;
    rect.w = surf -> w;
    rect.h = surf -> h;

    SDL_FreeSurface(surf);
    SDL_RenderCopy(renderer, text, nullptr, &rect);
    SDL_DestroyTexture(text);
}

void Game::loadMap(const char* filename)
{
    Object temp;
    temp.setTexture("res/tileset.png", renderer);
    int current, mx, my, mw, mh;
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Failed to open map file." << std::endl;
        return;
    }
    in >> mw >> mh >> mx >> my;
    for (int i = 0; i < mh; i++) {
        for (int j = 0; j < mw; j++) {
            if (in.eof()) {
                std::cout << "Reached end of map file too soon." << std::endl;
                return;
            }
            in >> current;
            if (current != 0)
            {
                temp.setSolid(true);
                temp.setSource((current - 1) * 32, 0, 32, 32);
                temp.setDest((j * tileSize) + mx, (i * tileSize) + my, tileSize, tileSize);
                temp.setId(current);
                if (current == 12 || current == 30 || current == 35 || current == 22)
                    temp.setSolid(false);
                map.push_back(temp);
            }
        }
    }
    in.close();
}

void Game::drawMap() {
    for (int i = 0; i < map.size(); i++)
    {
        if ( ( map[i].getDX() >= (mapX - tileSize)) && (map[i].getDX() <= (mapX + tileSize + windowWidth)) && (map[i].getDY() >= (mapY - tileSize)) && (map[i].getDY() <= (mapY + tileSize + windowHeight)))
            drawObject( map[i] ) ;
    }
}

void Game::scroll(int x, int y)
{
    for (int i = 0; i < map.size(); i++) {
        map[i].setDest(map[i].getDX() + x, map[i].getDY() + y);
    }
}

bool Game::isRunning() const
{
    return gameRunning;
}

bool Game::collision(Object a, Object b)
{
    if ( ( a.getDX() < ( b.getDX() + b.getDW() ) ) && ( ( a.getDX() + a.getDW() ) > b.getDX() )
        && ( a.getDY() < ( b.getDY() + b.getDH() ) ) && ( ( a.getDY() + a.getDH() ) > b.getDY() ) ) {
        return true;
    }
    else
        return false;
}

Game::~Game() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
}