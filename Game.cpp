#include "Game.h"
#include <vector>

const int thickness = 15;
const int paddleH = 100.0f;
const int ballMax = 2;

Game::Game()
	:mWindow(nullptr)
	,mRenderer(nullptr)
	,mTicksCount(0)
	,mIsRunning(true)
	,mPaddleDir(0)
	,mPaddleDir2(0)
{

}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unenable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Pong",
		100,
		100,
		1024,
		768,
		0
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mPaddlePos2.x = 994.0f;
	mPaddlePos2.y = 768.0f / 2.0f;
	//mBallPos.x = 1024.0f / 2.0f;
	//mBallPos.y = 768.0f / 2.0f;
	//mBallVel.x = -200.0f;
	//mBallVel.y = 235.0f;

	balls[0].ballPos.x = 1024.0f / 2.0f;
	balls[0].ballPos.y = 768.0f / 2.0f;
	balls[0].ballVel.x = -200.0f;
	balls[0].ballVel.y = 235.0f;

	balls[1].ballPos.x = 1024.0f / 2.0f;
	balls[1].ballPos.y = 768.0f / 3.0f;
	balls[1].ballVel.x = 200.0f;
	balls[1].ballVel.y = -235.0f;

	return true;
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}


	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W]) 
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}

	mPaddleDir2 = 0;
	if (state[SDL_SCANCODE_I])
	{
		mPaddleDir2 -= 1;
	}
	if (state[SDL_SCANCODE_K])
	{
		mPaddleDir2 += 1;
	}
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f) 
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();
	if (mPaddleDir != 0) 
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos.y = paddleH / 2.0 + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	if (mPaddleDir2 != 0)
	{
		mPaddlePos2.y += mPaddleDir2 * 300.0f * deltaTime;
		if (mPaddlePos2.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos2.y = paddleH / 2.0 + thickness;
		}
		else if (mPaddlePos2.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlePos2.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

#if 0
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	float diff = mPaddlePos.y - mBallPos.y;
	float diff2 = mPaddlePos2.y - mBallPos.y;
	diff = (diff > 0.0f) ? diff : -diff;
	diff2 = (diff2 > 0.0f) ? diff2 : -diff2;
	if (
		diff <= paddleH / 2.0f
		&& mBallPos.x <= 25.0f && mBallPos.x >= 20.0f
		&& mBallVel.x < 0.0f
		)
	{
		mBallVel.x *= -1.0f;
	}
	else if (
		diff2 <= paddleH / 2.0f
		&& mBallPos.x <= 1004.0f && mBallPos.x >= 999.0f
		&& mBallVel.x >= 0.0f
		)
	{
		mBallVel.x *= -1.0f;
	}
	else if (mBallPos.x <= 0.0f || mBallPos.x >= 1024.0f)
	{
		mIsRunning = false;
	}
	//else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
	//{
	//	mBallVel.x *= -1.0f;
	//}

	if (mBallPos.y <= thickness && mBallVel.y < 0.0)
	{
		mBallVel.y *= -1;
	}
	else if (mBallPos.y >= (768 - thickness)
		&& mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}

	*/
#else
	for (int i = 0; i < ballMax; i++)
	{
		balls[i].ballPos.x += balls[i].ballVel.x * deltaTime;
		balls[i].ballPos.y += balls[i].ballVel.y * deltaTime;

		float diff = mPaddlePos.y - balls[i].ballPos.y;
		float diff2 = mPaddlePos2.y - balls[i].ballPos.y;
		diff = (diff > 0.0f) ? diff : -diff;
		diff2 = (diff2 > 0.0f) ? diff2 : -diff2;
		if (
			diff <= paddleH / 2.0f
			&& balls[i].ballPos.x <= 25.0f && balls[i].ballPos.x >= 20.0f
			&& balls[i].ballVel.x < 0.0f
			)
		{
			balls[i].ballVel.x *= -1.0f;
		}
		else if (
			diff2 <= paddleH / 2.0f
			&& balls[i].ballPos.x <= 1004.0f && balls[i].ballPos.x >= 999.0f
			&& balls[i].ballVel.x >= 0.0f
			)
		{
			balls[i].ballVel.x *= -1.0f;
		}
		else if (balls[i].ballPos.x <= 0.0f || balls[i].ballPos.x >= 1024.0f)
		{
			mIsRunning = false;
		}
		//else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
		//{
		//	mBallVel.x *= -1.0f;
		//}

		if (balls[i].ballPos.y <= thickness && balls[i].ballVel.y < 0.0)
		{
			balls[i].ballVel.y *= -1;
		}
		else if (balls[i].ballPos.y >= (768 - thickness)
			&& balls[i].ballVel.y > 0.0f)
		{
			balls[i].ballVel.y *= -1;
		}
	}

#endif

}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(
		mRenderer,
		0,
		0,
		255,
		255
	);

	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	SDL_Rect wall
	{
		0,
		0,
		1024,
		thickness
	};

	SDL_RenderFillRect(mRenderer, &wall);

	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//wall.x = 1024 - thickness;
	//wall.y = 0;
	//wall.w = thickness;
	//wall.h = 1024;
	//SDL_RenderFillRect(mRenderer, &wall);

	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	SDL_Rect paddle2{
		static_cast<int>(mPaddlePos2.x),
		static_cast<int>(mPaddlePos2.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle2);

	for (int i = 0; i < ballMax; i++) {
		SDL_Rect ball{
			static_cast<int>(balls[i].ballPos.x - thickness / 2),
			static_cast<int>(balls[i].ballPos.y - thickness / 2),
			thickness,
			thickness
		};


		SDL_RenderFillRect(mRenderer, &ball);
	}

	SDL_RenderPresent(mRenderer);
}

