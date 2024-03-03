#ifndef  HELLO_WORLD_H_
#define  HELLO_WORLD_H_

typedef
	enum eventID {
		EVID_NONE,
		EVID_UNKNOWN,
		EVID_KEY,
		EVID_TICK,
	}
eventID_t;

typedef
	enum animID {
		ANIM_TEXT,
		ANIM_BALL,
		ANIM_COFFEE,
		ANIM_CNT  // MUST be last
	}
animID_t;

typedef
	enum dir {
		DIR_NONE = 0x00,
		DIR_U    = 0x01,
		DIR_D    = 0x02,
		DIR_L    = 0x04,
		DIR_R    = 0x08,
		DIR_UL   = DIR_U | DIR_L,
		DIR_UR   = DIR_U | DIR_R,
		DIR_DL   = DIR_D | DIR_L,
		DIR_DR   = DIR_D | DIR_R,
	}
dir_t;

typedef
	struct eventMsg {
		eventID_t   id;     // --> local
		InputEvent  input;  // --> applications/input/input.h
	}
eventMsg_t;

typedef 
	struct state {
		// The OS is threaded, so we will protect these state variables with a mutex
		//   --> furi/core/mutex.*
		FuriMutex*   mutex;

		// Animation is a classic bouncing icon
		bool         animate;  // true -> animation enabled
		animID_t     animID;   // which logo
		dir_t        dir;      // animation direction

		// We will need a timer to run the animation
		FuriTimer*   timer;    // the timer
		uint32_t     timerHz;  // system ticks per second
		int          fps;      // animation frames-per-second

		// x,y coords of icon
		int          x;        // current x coord
		int          y;        // current y coord

		Font         font;     // Font for...
		char*        text;     //   Bouncing text

		Font 	     fontTwo;    // Font 2
		char*        textTwo;    // Text 2

		int          ballR;    // Ball radius

		// movement limits
		int          cnvW;     // canvas width
		int          minX;     // min x coord
		int          maxX;     // max x coord

		int          cnvH;     // canvas height
		int          minY;     // min x coord
		int          maxY;     // max y coord
	} 
state_t;

#endif //BC_DEMO_H_
