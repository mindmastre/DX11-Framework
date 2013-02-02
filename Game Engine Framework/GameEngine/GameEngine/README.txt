Things of importance

	Here are some ideas you might need to know to help understand
some of my coding choices.

***	This concept may end up being rendered useless depending on how hard it would be to integrate multithreading into the project,
as I just realized after writing this read me that it would be necessary, so take these ideas with a grain of salt as we might have to
rework some or many of the ideas. ***

*** Make sure each animation has its own animation file (.md5anim) otherwise there will be no way to differ the animations by frame, due to how the loader is set up ***

1) The 'Game' folder is where the game should be built. It is like the setup for everything game related.
	Use GameMain.cpp to initialize and update game related code
2) For anything the user would need to change as far as settings are concerned use the game options.
	To include the game options for use anywhere, just include 'GameOptions.h'. There is a global used to reference options
	called 'options'. To change are access options use the appropriate function. EG. options->FullScreen() will return the fullScreen value,
	while options->FullScreen(0) will disable fullscreen if options are unlocked
3) GameMain.cpp should only reference GameInterface.h and cpp, which is essentially the engine interface
4) The engine interface should handle everything in the backend. EG. if you want to add an entity to the game, you would say engine->AddEntity(...)
	The AddEntity function would built the entity and all related information, like linking the proper model, activating proper AI, physics, etc.
5) The ModelManager and TextureManager are meant to be references, not containers. What I mean is, it is processer intensive to parse a model file everytime
	you load a new model, so the model loader just creates the master model. You should create a copy of the model to use as the actual model for updating and rendering.
	It would be more efficient to just have one model loaded and use it to update in each location needed, which it currently is not doing. That may be something we need to discuss
	As for the TextureManager, There shouldn't be any need to have multiple copies of the same texture, so each texture loaded should just be pointed to by models
6) The way shaders are done will need to be overhauled or rewritten completely to accomodate for the uber shader, so that is something that needs to be done
7) The 'Utilities' folder is there for anything multiple interfaces would need, like a uniform vector3 class, as well as a conversion class for transfering from my vector stuff to directx vector stuff
8) The 'Shared Resources' folder is used to hold anything that would be shared memory, like base entities, or a messaging system, if we are creating a dll engine with no cross core communication
9) The project is currently set up to be pretty efficient as far as memory leaks are involved, so to prevent future problems, this idea should be kept in mind

*** The next ideas are stuff that arent implemented, but intended ***

10) The render order needs to be set up so that all transparent objects are rendered at the correct time and all together, so we dont have a repeat of the xray problems from senior project.
	This should apply to other model groups as well. On topic, There needs to be classification containers in the GraphicsInterface where these classified models are stored
11) I set up an 'AnimationDefinitions.h' file where animations can be defined. This idea might not be used, or may just be setup as a text file. It as just an idea I had to keep track of what animations
	are used and how to load them or set them
12) There are some things we may want to set up for debugging purposes, like pause engine functionality or pause core functionality. Another thing is pause animations functionality so that we can stop all animations while
	keeping everything else running.
13) Lastly, with all these ideas, we should probably set up a formal layout of what everything is going to be/do so crap like this readme can go burn in a fire. Sorry for the long list, but it might help familiarize yourself
	with what I have coded so far. If you have any questions, just ask. Im sure there are things I forgot to add to this readme