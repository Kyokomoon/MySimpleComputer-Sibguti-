enum keys
{
  KEY_L = 0,
  KEY_S,
  KEY_R,
  KEY_T,
  KEY_I,
  KEY_E,
  KEY_F5,
  KEY_F6,
  KEY_ENTER,
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT
};

int rk_readkey (enum keys *key);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);