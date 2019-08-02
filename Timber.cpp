#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf; 
using namespace std;

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//where is the player Brunches
//Left or Right
enum class side {LEFT, RIGHT, NONE};
side branchPositions[NUM_BRANCHES];

int main()
{
	// Creating Video Mode Object
	VideoMode vm(1920,1080);	// resolution of player screen

	//Create & open a window for the Game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	//Creating Background
		Texture textureBackground;							//Create a Texture to hold a graphic on GPU
		textureBackground.loadFromFile("graphics/background.jpg"); //Load a graphic into Texture
		Sprite spriteBackground;							//Create a Sprite
		spriteBackground.setTexture(textureBackground);		//Attach the texture to the Sprite
		spriteBackground.setPosition(585, 5);				//Set spriteBackground to cover the screen

	//Creating a Tree base
		Texture textureTreeBase;							//Create a Texture to hold a graphic on GPU
		textureTreeBase.loadFromFile("graphics/base.png");  //Load a graphic into Texture
		Sprite spriteTreeBase;							    //Create a Sprite
		spriteTreeBase.setTexture(textureTreeBase);			//Attach the texture to the Sprite
		spriteTreeBase.setPosition(841, 854);				//Set spriteTreeBase to cover the screen

	//Creating a Tree body
		Texture textureTreeBody;							//Create a Texture to hold a graphic on GPU
		textureTreeBody.loadFromFile("graphics/body.png");  //Load a graphic into Texture
		Sprite spriteTreeBody;							    //Create a Sprite
		spriteTreeBody.setTexture(textureTreeBody);			//Attach the texture to the Sprite
		spriteTreeBody.setPosition(855, 0);				//Set spriteTreeBody to cover the screen

	//Preparing a Bird
		Texture textureBird;						    //Create a Texture to hold a graphic on GPU
		textureBird.loadFromFile("graphics/bird1.png"); //Load a graphic into Texture
		Sprite spriteBird;							    //Create a Sprite
		spriteBird.setTexture(textureBird);			    //Attach the texture to the Sprite
		spriteBird.setPosition(700, 60);				//Set spriteBird to cover the screen

		//Creating left Tap
		Texture textureTap1;							 
		textureTap1.loadFromFile("graphics/left.png");   
		Sprite spriteTap1;								 
		spriteTap1.setTexture(textureTap1);				 
		spriteTap1.setPosition(795, 906);				 

		//Creating right Tap
		Texture textureTap2;							 
		textureTap2.loadFromFile("graphics/right.png");  
		Sprite spriteTap2;								 
		spriteTap2.setTexture(textureTap2);				 
		spriteTap2.setPosition(1070, 910);				 

		//Creating logo
		Texture textureLogo;							 
		textureLogo.loadFromFile("graphics/logo1.png");  
		Sprite spriteLogo;								 
		spriteLogo.setTexture(textureLogo);				 
		spriteLogo.setPosition(735, 100);			

		//Creating made by
		Texture textureMade;							 
		textureMade.loadFromFile("graphics/made by.png");   
		Sprite spriteMade;								 
		spriteMade.setTexture(textureMade);				 
		spriteMade.setPosition(1000, 380);

		//Creating Press Enter
		Texture textureEnter;
		textureEnter.loadFromFile("graphics/enter.png");
		Sprite spriteEnter;
		spriteEnter.setTexture(textureEnter);
		spriteEnter.setPosition(815, 600);

		//Creating Win
		Texture textureWin;
		textureWin.loadFromFile("graphics/win.png");
		Sprite spriteWin;
		spriteWin.setTexture(textureWin);
		spriteWin.setPosition(735, 100);

		//Creating Dead
		Texture textureDead;
		textureDead.loadFromFile("graphics/Dead.png");
		Sprite spriteDead;
		spriteDead.setTexture(textureDead);
		spriteDead.setPosition(735, 100);

		//Creating Time Out
		Texture textureTimeOut;
		textureTimeOut.loadFromFile("graphics/time out.png");
		Sprite spriteTimeOut;
		spriteTimeOut.setTexture(textureTimeOut);
		spriteTimeOut.setPosition(743, 100);

		bool birdActive = false;						// Is Bird currently Moving?
		float birdSpeed = 0.0f;							//	How fast bird can fly?

	//Makeing 3 Cloud Sprite from 1 texture
		Texture textureCloud;								//Create a Texture to hold a graphic on GPU
		textureCloud.loadFromFile("graphics/cloud.png");	//Load a graphic into Texture

		Sprite spriteCloud1;		//Create 3 cloud Sprites
		Sprite spriteCloud2;
		Sprite spriteCloud3;

		spriteCloud1.setTexture(textureCloud);  	//Attach the texture to the Sprite
		spriteCloud2.setTexture(textureCloud);
		spriteCloud3.setTexture(textureCloud);

		spriteCloud1.setPosition(600, 60);		//Set spriteCloud to cover the screen
		spriteCloud2.setPosition(1000, 60);
		spriteCloud3.setPosition(800,60);

		bool cloud1Active = false;			// Is Cloud1 currently Moving?
		bool cloud2Active = false;			// Is Cloud2 currently Moving?
		bool cloud3Active = false;			// Is Cloud3 currently Moving?

		float cloud1Speed = 0.0f;		//	How fast cloud1 can fly?
		float cloud2Speed = 0.0f;		//	How fast cloud2 can fly?
		float cloud3Speed = 0.0f;		//	How fast cloud3 can fly?

		//Creating Outline of Time bar
		Texture textureTimeBar;							//Create a Texture to hold a graphic on GPU
		textureTimeBar.loadFromFile("graphics/blood_bg.png");  //Load a graphic into Texture
		Sprite spriteTimeBar;							    //Create a Sprite
		spriteTimeBar.setTexture(textureTimeBar);			//Attach the texture to the Sprite
		spriteTimeBar.setPosition(810, 970);

		//Variable to control time itself
		Clock clock;

		//Time Bar
		RectangleShape timeBar;
		float timeBarStartWidth = 277;
		float timeBarHeight = 50;
		timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
		timeBar.setFillColor(Color::Red);
		timeBar.setPosition(965 - timeBarStartWidth / 2, 985);

		Time gameTimeTotal;
		float timeRemaining = 5.0f;
		float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

		//Track whether the game is running
		bool paused = true;

		//RandX
		int x = 0;

		//on
		bool On = false;

		//Time Out
		bool TimeOut = false;

		//Dead
		bool dead = false;
		
		//Win
		bool win = false;

		//Draw some text
		int score = 0;
		
		sf::Text scoreText;

		//Choosing Fonts
		Font font;
		font.loadFromFile("fonts/KOMIKAX_.ttf");

		//Set fonts to message
		scoreText.setFont(font);

		//Assign the actual Message
		scoreText.setString("score = 0");

		//Making Fonts Size
		scoreText.setCharacterSize(30);

		//choose a color
		scoreText.setFillColor(Color::Black);

		//Position of Text
		scoreText.setPosition(885, 920);

		//Prepare 5 Branches
		Texture textureBranch;
		textureBranch.loadFromFile("graphics/branch.png");
		//set texture to each sprites
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			branches[i].setTexture(textureBranch);
			branches[i].setPosition(-2000, -2000);
			
			//Set the sprites origin position to dead centre
			//we can then spin it round without changing its position
			branches[i].setOrigin(220, 20);
		}

		//Prepare the player
		Texture texturePlayer;
		texturePlayer.loadFromFile("graphics/Player.png");
		Sprite spritePlayer;
		spritePlayer.setTexture(texturePlayer);
		spritePlayer.setPosition(670, 690);

		//Player starts on the Left
		side playerSide = side::LEFT;

		//Prepare the Gravestone
		Texture textureRIP;
		textureRIP.loadFromFile("graphics/rip.png");
		Sprite spriteRIP;
		spriteRIP.setTexture(textureRIP);
		spriteRIP.setPosition(710, 910);

		//Prepare the playerLEFT
		Texture texturePlayerLeft;
		texturePlayerLeft.loadFromFile("graphics/PlayerLeft.png");
		Sprite spritePlayerLeft;
		spritePlayerLeft.setTexture(texturePlayerLeft);
		spritePlayerLeft.setPosition(680, 728);

		//Prepare the playerRight
		Texture texturePlayerRight;
		texturePlayerRight.loadFromFile("graphics/PlayerRight.png");
		Sprite spritePlayerRight;
		spritePlayerRight.setTexture(texturePlayerRight);
		spritePlayerRight.setPosition(998, 728);

		//Prepare the flying LOG
		Texture textureLog;
		textureLog.loadFromFile("graphics/log.png");
		Sprite spriteLog;
		spriteLog.setTexture(textureLog);
		spriteLog.setPosition(855, 620);

		//Other useful infos
		bool logActive = false;
		float logSpeedX = 1000;
		float logSpeedY = -1500;

		//Control the player input
		bool acceptInput = false;

		//Prepare the chop Sound
		SoundBuffer chopBuffer;
		chopBuffer.loadFromFile("sound/chop.wav");
		Sound chop;
		chop.setBuffer(chopBuffer);

		//Prepare the Death Sound
		SoundBuffer deathBuffer;
		deathBuffer.loadFromFile("sound/death.wav");
		Sound death;
		death.setBuffer(deathBuffer);

		//Prepare the Game End Sound
		SoundBuffer endBuffer;
		endBuffer.loadFromFile("sound/game ends.wav");
		Sound end;
		end.setBuffer(endBuffer);

		//Prepare the Win Music
		SoundBuffer winBuffer;
		winBuffer.loadFromFile("sound/win.wav");
		Sound winSound;
		winSound.setBuffer(winBuffer);

		//Prepare the Game Music
		SoundBuffer enterBuffer;
		enterBuffer.loadFromFile("sound/enter.wav");
		Sound enter;
		enter.setBuffer(enterBuffer);


	while (window.isOpen())
	{
		// Handle Player INPUT

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::KeyReleased && !paused)
				{
					//listen for keypress again
					acceptInput = true;
					
				}
			}

			//Closing Window
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
					window.close();
			}

			//Start the Game
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				paused = false;
				On = true;

				//draw player in normal position
				window.draw(spritePlayer);

				//Reset the time & the Score
				score = 0;
				timeRemaining = 5;

				//Make all Branches dissappear
				for (int i = 0; i < NUM_BRANCHES; i++)
				{
					branchPositions[i] = side::NONE;
				}
				//make sure the Gravestone is Hidden
				spriteRIP.setPosition(710, 2000);
				//Move the player into position
				spritePlayer.setPosition(660, 690);
				acceptInput = true;

				enter.play();
			}

			//wrap the player control to make sure
			// we are accepting input
			if (acceptInput)
			{
				//First handle if player is pressing Right cursor key
				if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
				{
					//Make sure player is on right side
					playerSide = side::RIGHT;
					score++;

					//Add the amount of time Remaining
					timeRemaining += (0.12 / score) + 0.10;
					
					
					spritePlayer.setPosition(1095, 690);

					//update Branches
					updateBranches(score);

					//set the log flying to the left
					spriteLog.setPosition(855, 722);
					logSpeedX = -5000;
					logActive = true;

					acceptInput = false;

					//play Chop sound
					chop.play();
				}
				//First handle if player is pressing Left cursor key
				else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
				{
					//Make sure player is on right side
					playerSide = side::LEFT;
					score++;

					//Add the amount of time Remaining
					timeRemaining += (0.12 / score) + 0.10;

					spritePlayer.setPosition(660, 690);

					//update Branches
					updateBranches(score);

					//set the log flying to the right
					spriteLog.setPosition(855, 720);
					logSpeedX = 5000;
					logActive = true;

					acceptInput = false;
					
					//play Chop sound
					chop.play();
				}

			}

		//Update the Scene
			if (paused)
			{
				srand((int)time(0));
				x = (rand() % 40) + 25;

				
			}
			if (!paused)
			{
				win = false;
				dead = false;
				On = true; // to show Player characters
				//Measure time
				Time dt = clock.restart(); //to restart clock each frame

				//Subtract from the amount of time Remaining
				timeRemaining -= dt.asSeconds();

				//Size up the the time bar
				timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

				if (timeRemaining <= 0.0f)
				{
					// pause the game
					paused = true;
					TimeOut = true;

					//play Death sound
					end.play();

				}

				//Setup the bird
				if (!birdActive)
				{
					//How fast the Bird is
					srand((int)time(0) * 10);
					birdSpeed = (rand() % 150) + 150;

					//How High is Bird
					srand((int)time(0) * 10);
					float height = (rand() % 400) + 160;
					spriteBird.setPosition(1300, height);
					birdActive = true;
				}
				else
					// Move the Bird
				{
					spriteBird.setPosition(
						spriteBird.getPosition().x - (birdSpeed * dt.asSeconds()),
						spriteBird.getPosition().y);

					// Has bird reached the right hand edge of the screen?
					if (spriteBird.getPosition().x < 600)
					{
						// set it up ready to be a whole new cloud for next frame
						birdActive = false;
					}
				}

				//Manage the Clouds

				//Cloud 1
				if (!cloud1Active)
				{
					//How fast the cloud is
					srand((int)time(0) * 25);
					cloud1Speed = (rand() % 250) + 70;

					//How High is cloud
					srand((int)time(0) * 10);
					float height = (rand() % 120) - 20;
					spriteCloud1.setPosition(500, height);
					cloud1Active = true;
				}
				else
					//move the cloud
				{
					spriteCloud1.setPosition(
						spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
						spriteCloud1.getPosition().y);

					// Has cloud reached the right hand edge of the screen?
					if (spriteCloud1.getPosition().x > 1100)
					{
						// set it up ready to be a whole new cloud for next frame
						cloud1Active = false;
					}
				}

				//Cloud 2
				if (!cloud2Active)
				{
					//How fast the cloud is
					srand((int)time(0) * 20);
					cloud2Speed = (rand() % 250) + 30;

					//How High is cloud
					srand((int)time(0) * 10);
					float height = (rand() % 150) + 20;
					spriteCloud2.setPosition(1100, height);
					cloud2Active = true;
				}
				else
					//move the cloud
				{
					spriteCloud2.setPosition(
						spriteCloud2.getPosition().x - (cloud2Speed * dt.asSeconds()),
						spriteCloud2.getPosition().y);

					// Has cloud reached the right hand edge of the screen?
					if (spriteCloud2.getPosition().x < 520)
					{
						// set it up ready to be a whole new cloud for next frame
						cloud2Active = false;
					}
				}

				//Cloud 3
				if (!cloud3Active)
				{
					//How fast the cloud is
					srand((int)time(0) * 10);
					cloud3Speed = (rand() % 150) + 50;

					//How High is cloud
					srand((int)time(0) * 20);
					float height = (rand() % 150) - 10;
					spriteCloud3.setPosition(500, height);
					cloud3Active = true;
				}
				else
					//move the cloud
				{
					spriteCloud3.setPosition(
						spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
						spriteCloud3.getPosition().y);

					// Has cloud reached the right hand edge of the screen?
					if (spriteCloud3.getPosition().x > 1100)
					{
						// set it up ready to be a whole new cloud for next frame
						cloud3Active = false;
					}
				}

				//Update the score text
				std::stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());


				//Update the Branch sprites
				for (int i = 0; i < NUM_BRANCHES; i++)
				{
					float height = (i * 150) + 10;
					if (branchPositions[i] == side::LEFT)
					{
						//Move the sprite to the LEFT side
						branches[i].setPosition(645, height);
						//Flip the sprite round the other tree
						branches[i].setRotation(180);
					}
					else if (branchPositions[i] == side::RIGHT)
					{
						//Move the sprite to the LEFT side
						branches[i].setPosition(1290, height);
						//Flip the sprite round the other tree
						branches[i].setRotation(0);
					}
					else
					{
						//Hide the Branch
						branches[i].setPosition(3000, height);
					}
				}

				//Handle Flying Log
				if (logActive)
				{
					spriteLog.setPosition(
						spriteLog.getPosition().x + 
						(logSpeedX * dt.asSeconds()),
						spriteLog.getPosition().y +
						(logSpeedY * dt.asSeconds()));

					//has the log reached the right hand edge
					if (spriteLog.getPosition().x < 450 ||
						spriteLog.getPosition().x > 1250)
					{
						//set it ready to be a new log
						logActive = false;
						spriteLog.setPosition(855, 630);
					}
				}
				
				//Has player been squished?
				if (branchPositions[5] == playerSide)
				{
					//death
					paused = true;
					acceptInput = false;
					dead = true;
					

					//hide player
					spritePlayer.setPosition(2000, 600);
					
					//Position of log after dead
					logActive = false;
					spriteLog.setPosition(855, 620);

					//play Death sound
					death.play();
				}

				
			}

			
		//Draw the Scene

			//Clear everything from the last frame
			window.clear();

			//Draw our game scene
			window.draw(spriteBackground);

			// Create the Parallax effects
			//Draw the Clouds
			window.draw(spriteCloud1);
			window.draw(spriteCloud2);
			window.draw(spriteCloud3);

			//Draw Birds
			window.draw(spriteBird);

			//Draw Trees
			window.draw(spriteTreeBase);
			window.draw(spriteTreeBody);

			//Draw the Branches
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				window.draw(branches[i]);
			}

			//Draw the Log
			window.draw(spriteLog);

			if (paused)
			{
				if (win == true)
				{
					//window.draw(spriteLogo);
					window.draw(spriteWin);
					window.draw(spriteEnter);
					window.draw(scoreText);
				}
				else if (dead == true)
				{
					spriteRIP.setPosition(710, 800);
					window.draw(spriteRIP);
					window.draw(spriteDead);
					window.draw(spriteEnter);
					window.draw(scoreText);
				}
				else if (TimeOut == true)
				{
					window.draw(spriteTimeOut);
					window.draw(spriteEnter);
					window.draw(scoreText);
				}
				else
				{
					window.draw(spriteLogo);
					window.draw(spriteMade);
					window.draw(spriteEnter);
				}
				On = false;
			}

			if (On == true)
			{
				//Draw the Player
				if (Keyboard::isKeyPressed(Keyboard::Left)|| Keyboard::isKeyPressed(Keyboard::A))
				{
					window.draw(spritePlayerLeft);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
				{

					window.draw(spritePlayerRight);
				}
				else
				{
					window.draw(spritePlayer);
				}

				//draw tap
				window.draw(spriteTap1);
				window.draw(spriteTap2);

				//Draw Time Bar Border
				window.draw(spriteTimeBar);

				//Draw the Time bar
				window.draw(timeBar);

				//Draw the score
				window.draw(scoreText);
			}

			//Show everything we just drew
			window.display();

			//Winning Condition
			if (score == x)
			{
				//Position of log after dead
				logActive = false;
				spriteLog.setPosition(855, 620);
				paused = true;
				win = true;
				enter.pause();
				winSound.play();
			}

	}
	return 0;
}

//Function 
void updateBranches(int seed)
{
	//Move all branches down to one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}
	//Spawn new branch at position 0
	//LEFT, RIGHT or None
	srand(time(NULL) + seed);
	int r = (rand() % 4);
	
	switch (r)
	{
	case 0:
		branchPositions[0] = side::LEFT;
		break;

	case 1:
		branchPositions[0] = side::RIGHT;
		break;

	default:
		branchPositions[0] = side::NONE;
		break;
	}
}
