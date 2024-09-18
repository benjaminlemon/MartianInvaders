//Project planning:
B Game
    1. startMenu
    2. gameOverMenu

Process Event():
    ~1. N player.move()
    ~2. B integrate player.move->processEvent()
    3. N player.shoot()
    4. B integrate player.shoot()->processEvent()

Update()
    1. B Enemy
        ~a. .updatePosition()
            aa. OOB
        ~b. .collision(bullets vector)
        ~c. .collision(player)
        ~d. .updateHealth(&bullet);
        ~e. .updateHealth(player);
    
    2. B Bullets
        ~a. .updatePosition()
            aa. OOB
        ~b. .collision(enemy vector);
        ~c. .destroy();
        ~d. bullet();
    
    3. N Player
        a. .updatePosition();
            aa. OOB
        b. .collision(enemy vector);
        c. .updateHealth()
        d. .destroy()
    
    4. B Game
        a .gameOver(&player);
    
B Render()
    1. render bullets
    2. render player
    3. render enemies