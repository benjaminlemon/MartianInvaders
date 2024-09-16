//Project planning:

//classes
Game:
<!---start()-->
<!----RenderWindow-->

-run()

--processEvents()
----keypress to move(a,w,s,d or arrowkeys)
------update location

----keypress to shoot(space)
------update-create bullet

----closed

--update()
----location:PC, NPC, Bullets
----health: PC, NPC
----destroy: PC, NPC, Bullets
----createNPC();

--render()
----pc
----npc
----bullets


<!--Character:-->


Player:
    private:
        health, fireRate, dmg, speed, sprite/img, location, 
    
    public:
        all getters
        all setters
\        shoot();
    https://www.sfml-dev.org/tutorials/2.6/graphics-transform.php

    built in function to move entities around;
<!--        destroyed();-->
        


Enemy:
    private: health, speed, sprite/img, location
    public: getters/setters
    updatelocation()
    destroyed-frame/health



Bullet:
    private:
        location, velocity/speed, 
    Public: 
        damage();
        updateLocation()
