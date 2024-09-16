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



PC:
    private:
        health, fireRate, dmg, speed, sprite/img, location, 
    
    public:
        all getters
        all setters
        shoot();
<!--        destroyed();-->
        


NPC:
    private: health, speed, sprite/img, location
    public: getters/setters, destroyed-frame/health



Bullet:
    private:
        location, velocity/speed, 
    Public: damage();
