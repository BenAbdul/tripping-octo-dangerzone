class Player
{
public:
	int Lives;
	int Ammo;
	int CurrentSelection;

	int xVel, yVel;
	int xPos, yPos;

	void HandleEvents();
	void UpdatePosition();
	void Render();
	void Fire();

	Player();
} Character;