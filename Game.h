#pragma once
#include "SDL.h"
#include <vector>

struct Vector2
{
	float x;
	float y;
};

struct Ball
{
	Vector2 ballPos;
	Vector2 ballVel;
};

class Game
{
public:
	Game();
	// Initialize the game
	bool Initialize();
	// Run the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;

	int mPaddleDir;
	int mPaddleDir2;
	Vector2 mPaddlePos;
	Vector2 mPaddlePos2;
	//Vector2	mBallPos;
	//Vector2 mBallVel;
	std::vector<Ball> balls = std::vector<Ball> (2);
};