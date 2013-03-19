int sideSize;
int colorCount;
color[] colors;

boolean chessboardBW;
void setup() {
  size(800, 600);
  sideSize = 150;
  chessboardBW = true;
  if(chessboardBW)
  {
  colorCount = 2;

  colors = new color[colorCount];
  colors[0] = color(255, 255, 255);
  colors[1] = color(0, 0, 0);
  }
  else
  {
  colorCount = 8;
  colors = new color[colorCount];
  colors[0] = color(0, 0, 0);
  colors[1] = color(255, 0, 0);
  colors[2] = color(255, 255, 0);
  colors[3] = color(0, 255, 0);
  colors[4] = color(0, 255, 255);
  colors[5] = color(0, 0, 255);
  colors[6] = color(255, 0, 255);  
  colors[7] = color(255, 255, 255);
  }}

void draw() 
{

  for(int i = 0; i < width/sideSize; i++)
  {
    for(int j = 0; j < height/sideSize; j++)
    {
     noStroke();
     fill(colors[(i+j)%colorCount]);
     rect(i*sideSize, j*sideSize, sideSize, sideSize);
    }
  }
  background(0);
}

void keyPressed()
{
  
  save("chessboard.jpg");
}
