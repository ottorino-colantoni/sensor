import toxi.geom.*;
import toxi.geom.mesh.*;
import toxi.processing.*;
import processing.serial.*;
import processing.opengl.*;

//variabili globali

ToxiclibsSupport gfx;
TriangleMesh mesh;

Serial serialPort;                         // The serial port
float[] angles = new float[3];

Quaternion quat = new Quaternion(1, 0, 0, 0);

void setup(){
  size(600, 600, P3D);
  mesh=(TriangleMesh)new STLReader().loadBinary(sketchPath("person.stl"),STLReader.TRIANGLEMESH);
  mesh.scale(5);
  smooth();
  gfx=new ToxiclibsSupport(this);
  //String portName = Serial.list()[0];
  String portName = "COM10";
  //String portName = "/dev/ttyUSB0";
  serialPort = new Serial(this, portName, 115200);
  for(int i=0; i<3; i++) {
    angles[i] = 0;
  }
  serialPort.bufferUntil('\n');
}


void draw(){
  for(int i=0; i<3; i++) {
    angles[i] = angles[i]*3.14/(180*67);
  }
  quat = Quaternion.createFromEuler(angles[1],angles[2],angles[0]);// Arduino Leonardo
  background(0);
  lights();  
  translate(width/2,height/2,0);
  float[] axis = quat.toAxisAngle();
  rotate(axis[0],- axis[1], axis[3], axis[2]);
  noStroke();
  fill(0, 0, 255, 255);
  gfx.mesh(mesh,true,0);
}

void serialEvent(Serial serialPort) {
  for(int i=0; i<3; i++) {
    try {
      angles[i] = Integer.parseInt(serialPort.readStringUntil(' ').trim());
    }
    catch(Exception e) {}
  }
}